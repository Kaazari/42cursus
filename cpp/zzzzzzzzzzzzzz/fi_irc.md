# ft_irc — Documentation complète pour la soutenance

## Table des matières
1. [Vue d'ensemble](#vue-densemble)
2. [Architecture du projet](#architecture-du-projet)
3. [Flux de données](#flux-de-données)
4. [Classe Client](#classe-client)
5. [Classe Channel](#classe-channel)
6. [Classe Server](#classe-server)
7. [Parser — Parseur / MakeTheCommand](#parser--parseur--makethecommand)
8. [Dispatcher — dispatchRawLine](#dispatcher--dispatchrawline)
9. [Commandes IRC — les builtins](#commandes-irc--les-builtins)
   - [PASS](#pass)
   - [NICK](#nick)
   - [USER](#user)
   - [JOIN](#join)
   - [PART](#part)
   - [PRIVMSG](#privmsg)
   - [KICK](#kick)
   - [INVITE](#invite)
   - [TOPIC](#topic)
   - [MODE](#mode)
   - [PING](#ping)
   - [QUIT](#quit)
10. [Codes de réponse IRC utilisés](#codes-de-réponse-irc-utilisés)
11. [Questions fréquentes en soutenance](#questions-fréquentes-en-soutenance)

---

## Vue d'ensemble

ft_irc est un serveur IRC implémenté en C++98. Il reçoit des connexions TCP de clients IRC (irssi, nc, etc.), parse leurs commandes, et applique la logique du protocole IRC.

```
Client IRC (irssi/nc)
       |
       | TCP (port 6667)
       v
  [ Server ]
       |
       |-- poll() surveille tous les fd simultanément
       |-- recv() lit les données brutes
       |-- reconstruit les lignes complètes (processClientBuffer)
       |-- parse la ligne (MakeTheCommand)
       |-- dispatch vers le bon handler (dispatchRawLine)
       |-- handler modifie Client / Channel
       |-- send() renvoie les réponses via output buffer
```

Le serveur est **non-bloquant** : un seul `poll()` surveille tous les file descriptors (serveur + tous les clients) en même temps. Jamais de `fork()`, jamais de threads.

---

## Architecture du projet

```
ft_irc/
├── include/
│   ├── Server.hpp       — classe principale, gère réseau + état global
│   ├── Client.hpp       — représente un client connecté
│   ├── Channel.hpp      — représente un salon IRC
│   ├── Parsing.hpp      — structure Parseur + déclaration MakeTheCommand
│   └── Commands.hpp     — déclarations de tous les handlers
├── src/
│   ├── Server.cpp       — implémentation réseau + dispatcher
│   ├── Client.cpp       — implémentation Client
│   ├── Channel.cpp      — implémentation Channel
│   ├── parsing/
│   │   └── parsing.cpp  — implémentation MakeTheCommand
│   └── commands/
│       ├── Pass.cpp
│       ├── Nick.cpp
│       ├── User.cpp
│       ├── Join.cpp
│       ├── Part.cpp
│       ├── Privmsg.cpp
│       ├── Kick.cpp
│       ├── Invite.cpp
│       ├── Topic.cpp
│       ├── Mode.cpp
│       └── Quit.cpp
└── main.cpp             — point d'entrée, parse port + password
```

---

## Flux de données

Voici ce qui se passe exactement quand un client tape `PRIVMSG #general :salut` :

```
1. poll() détecte POLLIN sur le fd du client
2. receiveFromClient() → recv() lit les octets bruts dans un buffer char[1024]
3. appendInput() ajoute ces octets au _input_buffer du client
4. processClientBuffer() cherche un '\n' dans le buffer
   → trouve "PRIVMSG #general :salut\r\n"
   → retire le \r et le \n
   → appelle handleClientLine(fd, "PRIVMSG #general :salut")
5. handleClientLine() → dispatchRawLine()
6. MakeTheCommand() parse la ligne :
   → _command = "PRIVMSG"
   → _args[0]  = "#general"
   → _args[1]  = "salut"
7. dispatchRawLine() appelle handlePrivmsg(*this, client, parsed)
8. handlePrivmsg() vérifie les erreurs, puis pour chaque membre du channel :
   → server.sendLine(membre->getFd(), ":toto!toto@localhost PRIVMSG #general :salut")
9. sendLine() → queueMessage() → appendOutput() sur le client destinataire
10. poll() détecte POLLOUT sur ce fd
11. sendToClient() → send() envoie les octets
```

Le message ne va **jamais directement** dans le send() — il passe toujours par le output buffer, et c'est poll() + sendToClient() qui gèrent l'envoi réel. C'est ça qui garantit le non-bloquant.

---

## Classe Client

**Fichiers** : `include/Client.hpp`, `src/Client.cpp`

Représente un client connecté. Chaque client a un fd unique (son socket).

### Attributs

| Attribut | Type | Rôle |
|---|---|---|
| `_fd` | `int` | File descriptor du socket du client |
| `_input_buffer` | `string` | Données reçues mais pas encore traitées |
| `_output_buffer` | `string` | Données en attente d'envoi |
| `_nickname` | `string` | Pseudo IRC (vide avant NICK) |
| `_username` | `string` | Nom d'utilisateur (vide avant USER) |
| `_realname` | `string` | Nom réel (vide avant USER) |
| `_passwordOk` | `bool` | true si PASS correct reçu |
| `_hasNick` | `bool` | true si NICK valide reçu |
| `_hasUser` | `bool` | true si USER valide reçu |
| `_channels` | `set<string>` | Noms des channels rejoints |

### Méthodes importantes

**`isRegistered()`** : retourne `_passwordOk && _hasNick && _hasUser`. C'est la condition pour qu'un client puisse utiliser JOIN, PRIVMSG, etc. Un client non-registered reçoit `451 ERR_NOTREGISTERED`.

**`appendInput()` / `eraseInput()`** : gèrent le buffer d'entrée. La couche réseau accumule les données reçues, le parser les consomme.

**`appendOutput()` / `eraseOutput()`** : gèrent le buffer de sortie. Les handlers écrivent dedans, poll() + sendToClient() envoient réellement.

**`joinChannel()` / `leaveChannel()`** : maintiennent la liste des channels côté client. Doit rester en sync avec `Channel._members`.

### Cycle de vie d'un client

```
connexion → Client(fd) créé, tous les flags à false
PASS ok   → _passwordOk = true
NICK ok   → _nickname = "toto", _hasNick = true
USER ok   → _username = "toto", _realname = "...", _hasUser = true
            → isRegistered() = true → envoi du 001 RPL_WELCOME
...utilisation normale...
QUIT/déco → cleanupClientFromChannels() + close(fd) + erase de _clients
```

---

## Classe Channel

**Fichiers** : `include/Channel.hpp`, `src/Channel.cpp`

Représente un salon IRC. Stocké dans `Server._channels` (map indexée par nom).

### Attributs

| Attribut | Type | Rôle |
|---|---|---|
| `_name` | `string` | Nom du channel, commence par `#` |
| `_topic` | `string` | Sujet du channel, vide par défaut |
| `_key` | `string` | Mot de passe (mode +k), vide = pas de key |
| `_userLimit` | `int` | Limite de membres (mode +l), 0 = illimité |
| `_inviteOnly` | `bool` | Mode +i : seuls les invités peuvent JOIN |
| `_topicRestricted` | `bool` | Mode +t : seuls les ops peuvent TOPIC |
| `_members` | `vector<Client*>` | Tous les membres actuels |
| `_operators` | `vector<Client*>` | Membres avec droits opérateur |
| `_invited` | `vector<Client*>` | Clients invités (via INVITE) |

### Constructeur

```cpp
Channel(const std::string& name, Client* creator)
```

Le créateur est automatiquement ajouté comme **membre ET opérateur**. C'est le comportement IRC standard : le premier à créer le channel en devient op.

### `removeMember()`

Quand un membre quitte (PART, KICK, déconnexion), `removeMember()` le retire aussi automatiquement de `_operators` et `_invited`. Pas besoin de le faire manuellement.

### `broadcast(message, exclude)`

Envoie un message à tous les membres. `exclude` permet d'exclure un client (ex: l'émetteur d'un PRIVMSG ne reçoit pas son propre message en retour du serveur).

**Note importante** : `broadcast()` utilise `appendOutput()` directement, sans activer `POLLOUT`. Dans les handlers, on utilise donc `server.sendLine()` en boucle sur les membres plutôt que `broadcast()`, pour que `enablePollOut()` soit appelé correctement.

### Relation Client ↔ Channel

```
Client._channels     = { "#general", "#cpp" }   ← juste les noms
Channel._members     = [ &client_toto, &client_bob ]  ← pointeurs

Ces deux structures doivent rester en sync :
- JOIN  → channel.addMember(&client) + client.joinChannel(name)
- PART  → channel.removeMember(&client) + client.leaveChannel(name)
- KICK  → channel.removeMember(target) + target.leaveChannel(name)
```

---

## Classe Server

**Fichiers** : `include/Server.hpp`, `src/Server.cpp`

Classe centrale. Gère la socket serveur, tous les clients, tous les channels, et la boucle poll().

### Attributs privés

| Attribut | Type | Rôle |
|---|---|---|
| `_port` | `int` | Port d'écoute |
| `_password` | `string` | Mot de passe requis (PASS) |
| `_server_fd` | `int` | Socket du serveur |
| `_running` | `bool` | Contrôle la boucle principale |
| `_poll_fds` | `vector<pollfd>` | Tous les fd surveillés par poll() |
| `_clients` | `map<int, Client>` | fd → Client |
| `_channels` | `map<string, Channel*>` | nom → Channel* |

### La boucle poll()

```cpp
void Server::run(void) {
    while (_running && !_stop_signal) {
        poll(&_poll_fds[0], _poll_fds.size(), -1); // bloque jusqu'à activité
        // pour chaque fd actif :
        //   si c'est _server_fd → acceptClient()
        //   si POLLIN            → receiveFromClient()
        //   si POLLOUT           → sendToClient()
        //   si POLLERR/POLLHUP   → disconnectClient()
    }
}
```

`poll()` est appelé une seule fois par itération et surveille **tous les fd** simultanément. C'est ce qui permet de gérer N clients sans bloquer.

### POLLIN vs POLLOUT

- **POLLIN** : toujours actif sur tous les fd — on veut toujours savoir si un client envoie quelque chose.
- **POLLOUT** : activé par `enablePollOut()` seulement quand `_output_buffer` contient des données à envoyer. Désactivé par `disablePollOut()` une fois le buffer vide. Cela évite de "spinner" sur POLLOUT quand il n'y a rien à envoyer.

### Reconstruction des lignes IRC

```cpp
void Server::processClientBuffer(int client_fd) {
    // cherche '\n' dans le input_buffer
    // extrait la ligne, retire le '\r' final
    // appelle handleClientLine() pour chaque ligne complète
    // les données incomplètes restent dans le buffer
}
```

Le protocole IRC peut arriver fragmenté (TCP ne garantit pas que `send("PASS monpass\r\n")` arrive en un seul `recv()`). `processClientBuffer()` reconstitue les lignes complètes avant de les traiter.

### cleanupClientFromChannels()

Appelé à chaque déconnexion (propre ou brutale). Retire le client de tous ses channels, notifie les autres membres avec un `QUIT`, supprime les channels vides.

### Méthodes publiques (appelées par les handlers)

| Méthode | Rôle |
|---|---|
| `sendLine(fd, msg)` | Envoie `msg + "\r\n"` au client |
| `queueMessage(fd, msg)` | Ajoute au output buffer + active POLLOUT |
| `getPassword()` | Retourne le mot de passe du serveur |
| `getClientByNick(nick)` | Cherche un client par son pseudo |
| `getChannel(name)` | Retourne un Channel* ou NULL |
| `createChannel(name, creator)` | Crée un channel, retourne le pointeur |
| `removeChannel(name)` | Supprime un channel vide |
| `getClients()` | Accès à la map complète des clients |
| `requestDisconnect(fd)` | Déconnecte proprement un client (utilisé par QUIT) |

---

## Parser — Parseur / MakeTheCommand

**Fichiers** : `include/Parsing.hpp`, `src/parsing/parsing.cpp`

### La structure Parseur

```cpp
class Parseur {
public:
    int                      _fd;      // fd du client qui a envoyé la commande
    std::string              _command; // ex: "PRIVMSG"
    std::vector<std::string> _args;    // ex: ["#general", "salut tout le monde"]
};
```

### MakeTheCommand()

Prend une ligne IRC brute (sans `\r\n`) et la découpe :

```
"KICK #general toto :comportement inapproprié"
→ _command = "KICK"
→ _args[0]  = "#general"
→ _args[1]  = "toto"
→ _args[2]  = "comportement inapproprié"
```

**Règle du trailing param** : si un mot commence par `:`, tout ce qui suit (espaces compris) est un seul paramètre. C'est ce qui permet d'avoir des messages avec des espaces.

```
"PRIVMSG #general :salut tout le monde"
→ _args[0] = "#general"
→ _args[1] = "salut tout le monde"   ← un seul token
```

---

## Dispatcher — dispatchRawLine

Dans `Server.cpp`, c'est le point de branchement entre le parser et les handlers :

```cpp
void Server::dispatchRawLine(int client_fd, const std::string& line) {
    Parseur parsed = MakeTheCommand(client_fd, line);
    Client& client = _clients[client_fd];

    if      (parsed._command == "PASS")    handlePass(*this, client, parsed);
    else if (parsed._command == "NICK")    handleNick(*this, client, parsed);
    else if (parsed._command == "USER")    handleUser(*this, client, parsed);
    else if (parsed._command == "JOIN")    handleJoin(*this, client, parsed);
    else if (parsed._command == "PART")    handlePart(*this, client, parsed);
    else if (parsed._command == "PRIVMSG") handlePrivmsg(*this, client, parsed);
    else if (parsed._command == "KICK")    handleKick(*this, client, parsed);
    else if (parsed._command == "INVITE")  handleInvite(*this, client, parsed);
    else if (parsed._command == "TOPIC")   handleTopic(*this, client, parsed);
    else if (parsed._command == "MODE")    handleMode(*this, client, parsed);
    else if (parsed._command == "PING")    sendLine(client_fd, ":server PONG server :" + ...);
    else if (parsed._command == "QUIT")    handleQuit(*this, client, parsed);
    else sendLine(client_fd, ":server 421 ... :Unknown command");
}
```

Chaque handler reçoit `Server&`, `Client&`, et `const Parseur&`.

---

## Commandes IRC — les builtins

### PASS

**Format** : `PASS <password>`

**Séquence d'enregistrement** : PASS doit être envoyé avant ou pendant l'enregistrement (avant que `isRegistered()` soit true). Il peut arriver avant, après, ou entre NICK et USER.

**Logique** :
```
1. args vide            → 461 ERR_NEEDMOREPARAMS
2. déjà registered      → 462 ERR_ALREADYREGISTERED
3. mauvais mot de passe → 464 ERR_PASSWDMISMATCH
4. succès               → setPasswordOk(true)
                          si isRegistered() → sendWelcome()
```

**Pourquoi sendWelcome dans PASS ?** : Si le client a déjà envoyé NICK et USER avant PASS, c'est PASS qui complète l'enregistrement → il doit envoyer le 001.

---

### NICK

**Format** : `NICK <nickname>`

**Nicknames valides** : lettres, chiffres, `-_[]\\^{}|`, max 30 caractères, ne peut pas commencer par un chiffre.

**Logique** :
```
1. args vide            → 431 ERR_NONICKNAMEGIVEN
2. nick invalide        → 432 ERR_ERRONEUSNICKNAME
3. nick déjà pris       → 433 ERR_NICKNAMEINUSE
4. succès               → setNickname() + setHasNick(true)
                          wasRegistered sauvegardé avant
                          si !wasRegistered && isRegistered() → sendWelcome()
```

**Pourquoi `wasRegistered` ?** : NICK peut être envoyé à n'importe quel moment (même après l'enregistrement pour changer de pseudo). On envoie le welcome uniquement si on **vient** de passer registered, pas à chaque NICK.

---

### USER

**Format** : `USER <username> <mode> <unused> :<realname>`

**Exemple** : `USER toto 0 * :Toto Real Name`
- `args[0]` = username ("toto")
- `args[1]` = mode ("0") — ignoré en pratique
- `args[2]` = unused ("*") — ignoré
- `args[3]` = realname ("Toto Real Name") — le trailing param

**Logique** :
```
1. args.size() < 4      → 461 ERR_NEEDMOREPARAMS
2. déjà registered      → 462 ERR_ALREADYREGISTERED
3. succès               → setUsername(args[0]) + setRealname(args[3]) + setHasUser(true)
                          même pattern wasRegistered que NICK
```

USER ne peut être envoyé **qu'une seule fois** — c'est pour ça que le check `isRegistered()` bloque le re-envoi.

---

### JOIN

**Format** : `JOIN <#channel> [key]`

**Création automatique** : si le channel n'existe pas, il est créé. Le client devient automatiquement membre et opérateur.

**Logique** :
```
1. pas registered       → 451 ERR_NOTREGISTERED
2. args vide            → 461 ERR_NEEDMOREPARAMS
3. nom ne commence pas par # → 403 ERR_NOSUCHCHANNEL
4. channel inexistant   → createChannel() + joinChannel() + broadcast JOIN + sendChannelInfo()
5. mode +i, pas invité  → 473 ERR_INVITEONLYCHAN
6. mode +k, mauvaise key → 475 ERR_BADCHANNELKEY
7. mode +l, channel plein → 471 ERR_CHANNELISFULL
8. déjà membre          → ignoré silencieusement
9. succès               → addMember() + joinChannel() + retirer des invités + broadcast JOIN + sendChannelInfo()
```

**sendChannelInfo()** envoie au nouveau membre :
- `331` ou `332` selon que le topic est vide ou non
- `353 NAMREPLY` : liste des membres avec `@` devant les ops
- `366 ENDOFNAMES`

**Pourquoi broadcast AVANT addMember dans la création** : `createChannel()` ajoute déjà le créateur comme membre, donc la boucle sur les membres inclut déjà le créateur. Pour un JOIN sur channel existant, on fait `addMember()` avant le broadcast pour que le nouveau reçoive aussi la notification.

---

### PART

**Format** : `PART <#channel> [:<reason>]`

**Logique** :
```
1. pas registered       → 451 ERR_NOTREGISTERED
2. args vide            → 461 ERR_NEEDMOREPARAMS
3. channel inexistant   → 403 ERR_NOSUCHCHANNEL
4. pas membre           → 442 ERR_NOTONCHANNEL
5. succès               → broadcast PART à tous (y compris celui qui part)
                          removeMember() + leaveChannel()
                          si channel vide → removeChannel()
```

**Pourquoi broadcaster à celui qui part aussi** : irssi a besoin de recevoir le message `PART` pour afficher "You have left #general" correctement.

---

### PRIVMSG

**Format** : `PRIVMSG <target> :<message>`

`target` peut être un channel (`#general`) ou un nickname (`toto`).

**Logique channel** :
```
1. pas registered           → 451
2. args vide                → 411 ERR_NORECIPIENT
3. args.size() < 2          → 412 ERR_NOTEXTTOSEND
4. channel inexistant       → 403
5. pas membre du channel    → 404 ERR_CANNOTSENDTOCHAN
6. succès                   → broadcast à tous sauf l'émetteur
```

**Logique nick** :
```
4. nick inexistant          → 401 ERR_NOSUCHNICK
5. succès                   → sendLine direct au destinataire
```

**Pourquoi exclure l'émetteur** : irssi affiche déjà le message localement sans attendre la réponse du serveur. Si le serveur le renvoyait en plus, l'utilisateur verrait son message en double.

---

### KICK

**Format** : `KICK <#channel> <nickname> [:<reason>]`

La raison par défaut est le nickname de la cible si non fournie.

**Logique** :
```
1. pas registered           → 451
2. args.size() < 2          → 461
3. channel inexistant       → 403
4. celui qui kick pas membre → 442
5. celui qui kick pas op    → 482 ERR_CHANOPRIVSNEEDED
6. cible inexistante        → 401
7. cible pas membre         → 441 ERR_USERNOTINCHANNEL
8. succès                   → broadcast KICK à tous (y compris la cible)
                              removeMember(target) + target.leaveChannel()
                              si channel vide → removeChannel()
```

**Broadcast avant remove** : la cible doit recevoir le message KICK avant d'être retirée du channel.

---

### INVITE

**Format** : `INVITE <nickname> <#channel>`

INVITE n'ajoute pas directement la cible au channel — elle l'ajoute à `_invited`. C'est le JOIN suivant qui vérifie `isInvited()`.

**Logique** :
```
1. pas registered           → 451
2. args.size() < 2          → 461
3. nick cible inexistant    → 401
4. channel inexistant       → 403
5. celui qui invite pas membre → 442
6. mode +i et pas op        → 482
7. cible déjà membre        → 443 ERR_USERONCHANNEL
8. succès                   → addInvited(target)
                              341 RPL_INVITING à celui qui invite
                              INVITE envoyé à la cible
```

---

### TOPIC

**Format** : `TOPIC <#channel> [:<topic>]`

Deux usages selon le nombre d'arguments :
- Un seul arg → **lecture** du topic actuel
- Deux args → **modification** du topic

**Logique** :
```
1. pas registered           → 451
2. args vide                → 461
3. channel inexistant       → 403
4. pas membre               → 442
5. args.size() < 2          → lecture : 331 (vide) ou 332 (topic existant)
6. mode +t et pas op        → 482
7. succès modification      → setTopic(args[1]) + broadcast TOPIC à tous
```

`TOPIC #general :` (trailing vide) **efface** le topic — `args[1]` sera une string vide.

---

### MODE

**Format** : `MODE <#channel> <+/-modes> [arguments...]`

**Modes supportés** :

| Mode | Argument | Description |
|---|---|---|
| `+i` / `-i` | aucun | Invite-only |
| `+t` / `-t` | aucun | Topic restreint aux ops |
| `+k <key>` / `-k` | le password pour +k | Channel key |
| `+o <nick>` / `-o <nick>` | le nickname | Donner/retirer op |
| `+l <n>` / `-l` | le nombre pour +l | Limite de membres |

**Parsing de la chaine de modes** :

```
"MODE #general +ik secret"
→ modeStr = "+ik"
→ modeArgs = ["secret"]

boucle sur modeStr :
  '+' → add = true
  'i' → handleModeI() — pas d'argument
  'k' → handleModeK() — consomme modeArgs[0] = "secret"
```

`argIndex` avance à chaque argument consommé par `k`, `o`, ou `l`.

**Logique générale** :
```
1. pas registered           → 451
2. args.size() < 2          → 461
3. channel inexistant       → 403
4. pas membre               → 442
5. pas opérateur            → 482
6. parser modeStr           → appel des sous-handlers
7. mode inconnu             → 472 ERR_UNKNOWNMODE
```

---

### PING

**Format** : `PING [:<token>]`

irssi envoie `PING` automatiquement pour vérifier que le serveur est vivant. Si le serveur ne répond pas avec `PONG`, irssi se déconnecte.

**Logique** : directement dans `dispatchRawLine`, sans handler séparé :
```cpp
sendLine(client_fd, ":server PONG server :" + (parsed._args.empty() ? "server" : parsed._args[0]));
```

---

### QUIT

**Format** : `QUIT [:<reason>]`

Déconnexion propre initiée par le client.

**Logique** :
```
1. broadcaster QUIT à tous les channels du client (sauf le client lui-même)
2. removeMember() sur chaque channel + supprimer si vide
3. ERROR :Closing Link: envoyé au client
4. requestDisconnect() → disconnectClient()
```

**Différence avec une déconnexion brutale (Ctrl+C)** : une déco brutale est détectée par `poll()` via `POLLHUP` ou `recv()` qui retourne 0. Dans les deux cas, `disconnectClient()` → `cleanupClientFromChannels()` fait le même nettoyage.

---

## Codes de réponse IRC utilisés

| Code | Nom | Quand |
|---|---|---|
| 001 | RPL_WELCOME | Enregistrement complet (PASS+NICK+USER) |
| 002 | RPL_YOURHOST | Avec le 001 |
| 003 | RPL_CREATED | Avec le 001 |
| 004 | RPL_MYINFO | Avec le 001 |
| 331 | RPL_NOTOPIC | Pas de topic sur le channel |
| 332 | RPL_TOPIC | Topic du channel |
| 341 | RPL_INVITING | Confirmation d'un INVITE réussi |
| 353 | RPL_NAMREPLY | Liste des membres d'un channel |
| 366 | RPL_ENDOFNAMES | Fin de la liste des membres |
| 401 | ERR_NOSUCHNICK | Nickname inexistant |
| 403 | ERR_NOSUCHCHANNEL | Channel inexistant |
| 404 | ERR_CANNOTSENDTOCHAN | Pas membre du channel |
| 411 | ERR_NORECIPIENT | PRIVMSG sans destinataire |
| 412 | ERR_NOTEXTTOSEND | PRIVMSG sans message |
| 421 | ERR_UNKNOWNCOMMAND | Commande inconnue |
| 431 | ERR_NONICKNAMEGIVEN | NICK sans argument |
| 432 | ERR_ERRONEUSNICKNAME | Nick avec caractères invalides |
| 433 | ERR_NICKNAMEINUSE | Nick déjà pris |
| 441 | ERR_USERNOTINCHANNEL | La cible n'est pas dans le channel |
| 442 | ERR_NOTONCHANNEL | Tu n'es pas dans le channel |
| 443 | ERR_USERONCHANNEL | La cible est déjà dans le channel |
| 451 | ERR_NOTREGISTERED | Pas encore registered |
| 461 | ERR_NEEDMOREPARAMS | Pas assez de paramètres |
| 462 | ERR_ALREADYREGISTERED | Déjà registered |
| 464 | ERR_PASSWDMISMATCH | Mauvais mot de passe |
| 471 | ERR_CHANNELISFULL | Channel plein (mode +l) |
| 472 | ERR_UNKNOWNMODE | Mode inconnu |
| 473 | ERR_INVITEONLYCHAN | Channel en mode +i |
| 475 | ERR_BADCHANNELKEY | Mauvaise key (mode +k) |
| 482 | ERR_CHANOPRIVSNEEDED | Pas opérateur du channel |

---

## Questions fréquentes en soutenance

**Pourquoi poll() et pas select() ou epoll() ?**
Le sujet demande poll() ou équivalent. poll() est plus portable et plus simple que epoll() (Linux only). select() a une limite sur le nombre de fd (FD_SETSIZE = 1024). poll() n'a pas cette limite.

**Pourquoi un seul poll() ?**
Le sujet l'impose. Un seul poll() surveille tous les fd simultanément : le server_fd pour les nouvelles connexions, et tous les client_fd pour les lectures/écritures. C'est efficace et non-bloquant.

**Comment gérez-vous les messages fragmentés ?**
TCP peut fragmenter les messages. `_input_buffer` accumule tout ce qui arrive. `processClientBuffer()` cherche `\n` et extrait les lignes complètes. Les données incomplètes restent dans le buffer jusqu'à la prochaine réception.

**Pourquoi pas de fork() ou de threads ?**
Le sujet l'interdit. La gestion simultanée de N clients est faite par poll() qui détecte quelle socket est prête et traite les événements séquentiellement.

**Comment fonctionne le non-bloquant ?**
Tous les fd sont mis en mode non-bloquant avec `fcntl(fd, F_SETFL, O_NONBLOCK)`. recv() et send() retournent immédiatement avec `EAGAIN`/`EWOULDBLOCK` si aucune donnée n'est disponible, au lieu de bloquer.

**Qui devient opérateur d'un channel ?**
Le premier client qui crée le channel (via JOIN sur un channel inexistant) devient automatiquement opérateur.

**Que se passe-t-il si un opérateur quitte le channel ?**
`removeMember()` le retire automatiquement de `_operators`. Si c'était le seul op et qu'il reste des membres, personne n'est plus op — c'est le comportement standard d'IRC basique. Les serveurs IRC avancés ont des mécanismes pour ré-attribuer les droits, mais ce n'est pas requis par le sujet.

**Comment tester le projet ?**
```bash
# Test basique avec nc
nc 127.0.0.1 6667
PASS monpass
NICK toto
USER toto 0 * :Toto Real Name

# Test avec irssi (client de référence)
irssi -c 127.0.0.1 -p 6667 -w monpass -n toto
```

**Que fait le serveur si le client envoie une commande inconnue ?**
```
421 ERR_UNKNOWNCOMMAND :Unknown command
```
Le client reste connecté, la commande est simplement ignorée.

**Pourquoi `wasRegistered` dans NICK et USER ?**
Pour éviter d'envoyer plusieurs 001. Si NICK arrive en dernier et que le client vient juste de passer registered, on envoie le welcome. Si NICK est envoyé après (changement de pseudo), `wasRegistered` était déjà true, donc pas de welcome.
