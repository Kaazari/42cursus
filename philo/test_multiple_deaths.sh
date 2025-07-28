#!/bin/bash

# Script pour tester plusieurs morts et détecter les doubles impressions

echo "=== TEST DE MULTIPLES MORTS ==="
echo ""

# Fonction pour tester et compter les morts
test_death_count() {
    local args="$1"
    local test_name="$2"
    local timeout_seconds="$3"

    echo "Test: $test_name"
    echo "Args: $args"
    echo "Timeout: ${timeout_seconds}s"

    # Exécuter avec timeout et capturer la sortie
    output=$(timeout $timeout_seconds ./philo $args 2>&1)
    exit_code=$?

    if [ $exit_code -eq 124 ]; then
        echo "❌ TIMEOUT - Programme arrêté après ${timeout_seconds}s"
        echo ""
        return
    fi

    # Compter les occurrences de "died"
    death_count=$(echo "$output" | grep -c "died")

    echo "Sortie complète:"
    echo "$output"

    if [ $death_count -eq 1 ]; then
        echo "✅ SUCCESS: 1 mort détectée (correct)"
    elif [ $death_count -eq 0 ]; then
        echo "⚠️  WARNING: Aucune mort détectée"
    else
        echo "❌ ERROR: $death_count morts détectées (DOUBLE IMPRESSION!)"
        echo "Détail des morts:"
        echo "$output" | grep "died" -n
    fi

    echo "----------------------------------------"
    echo ""
}

# Tests qui forcent vraiment la mort
echo "1. Test avec temps de repas très long (doit tuer)"
test_death_count "5 50 2000 2000" "Temps de repas très long" 10

echo "2. Test avec temps de sommeil très long (doit tuer)"
test_death_count "5 50 200 2000" "Temps de sommeil très long" 10

echo "3. Test avec temps de repas et sommeil très longs"
test_death_count "5 50 2000 2000" "Repas et sommeil très longs" 10

echo "4. Test avec 10 philosophes et temps longs"
test_death_count "10 50 2000 2000" "10 philosophes temps longs" 10

echo "5. Test avec 20 philosophes et temps longs"
test_death_count "20 50 2000 2000" "20 philosophes temps longs" 10

echo "6. Test avec 50 philosophes et temps longs"
test_death_count "50 50 2000 2000" "50 philosophes temps longs" 10

echo "7. Test avec 100 philosophes et temps longs"
test_death_count "100 50 2000 2000" "100 philosophes temps longs" 10

echo "=== TESTS MULTIPLES TERMINÉS ==="
