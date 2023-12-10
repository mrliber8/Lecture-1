#! /usr/bin/bash

# Het script accepteert twee parameter. 
# - De eerste parameter is de directory waar de foto’s staan. 
# - De tweede parameter bestaat uit de aanduiding “maand” of “week”. 


echo "De foto's staan op $1"
echo "De foto's worden verplaatst met als tijdspan $2"

#Als het script wordt gestart zal deze afhankelijk van de tweede parameter, 
#de foto’s die ouder zijn dan de gekozen optie naar een (nieuw te creëren) folder verplaatsen. 
#Bijvoorbeeld als er als tweede parameter “week” wordt gekozen, dan verplaatst het script de foto’s 
#in de map naar (nieuw te creëren) submappen met het corresponderende weeknummers. 

#Bij het verplaatsen wordt het origineel pas gewist als er gecontroleerd is of de kopieerslag succesvol 
#is geweest. Dit los je op door de hash (bv. m.b.v. MD5sum) van beide foto’s te vergelijken. Als deze 
#gelijk zijn dan pas verwijder je de foto van de originele locatie. 


# Stap 1: Check of de meegegeven parameter kloppen

if [ -z "$1" ]; then
    echo "De path locatie is niet gegeven, run het script opnieuw"
    exit 1
elif [ ! -d "$1" ]; then
    echo "De path locatie bestaat niet, run het script opnieuw"
    exit 1
fi

if [ -z "$2" ]; then
    echo "De week of maand notatie is niet gegeven, run het script opnieuw"
    exit 1
elif [ "$2" != "maand" ] && [ "$2" != "week" ]; then
    echo "De week of maand notatie is niet correct gegeven, run het script opnieuw en geef maand of week als notatie."
    exit 1
fi


# Dit maakt testen handiger
BASE_DIR="c/Users/patrick/Downloads/Lecture 1 Demo code(2)/Lecture 1/Linux/random"
cd "/mnt/c/Users/patrick/Downloads/Lecture 1 Demo code(2)/Lecture 1/Linux/random"

# Wat is d ehuidige datum?
current_date=$(date +%s)

for f in *.png *.jpg; do
    # Stap 2: Krijg de tijden van de file
    # Krijg de jaar tijden van de file
    year="$(date -d "$(stat -c %y "$f")" +%Y)"
    # Krijg de maand tijden van de file
    month="$(date -d "$(stat -c %y "$f")" +%B)"
    # Krijg de week tijden van de file
    week="$(date -d "$(stat -c %y "$f")" +%U)"
    # Datum sinds 1 jan 1970 voor het checken van het verschil
    oudheid="$(date -d "$(stat -c %y "$f")" +%s)"

    # Verschil in dagen, zit 86400 sec in een dag
    verschil=$(( (current_date - oudheid) / 86400 ))
    # Echo voor testen
    echo "Deze foto is $verschil dagen oud"

    # Echo's voor testen
    # Eerst testen voor een maand en daarna voor een week, want als die voor een maand triggert
    # dan triggert die natuurlijk ook voor een week....
    if [ $verschil -ge 30 ]; then
        echo "$f is langer dan een maand oud"
    elif [ $verschil -ge 3 ]; then
        echo "$f is langer dan een week oud"
    fi

    # Logica van de if en elif is hetzelfde, waarschijnlijk als ik een OR achter de if plaats met de 
    # Conditie van de elif dan werkt het ook, maar effeciente code staat niet in de opdracht :) Dus 
    # Voor nu laat ik het gewoon zo want het duurde al even voordat het werkte... Beter inefficient en
    # Werkend dan niet werkend



    
    if [ $2 == "maand" ] && [ $verschil -gt 30 ]; then

        # Stap 3: Check of de folder bestaat, zo niet --> aanmaken
        if [ ! -d "$year/$month/$week" ]; then
            mkdir -p "$year/$month/$week"
            echo "Folder $year/$month/$week aangemaakt"
        else
            echo "Folder $year/$month/$week bestaat al"
        fi

        # Stap 4: Kopieer het bestand
        cp "$f" "$year/$month/$week"
        new_file="$year/$month/$week/$f"
    elif [ $2 == "week" ] && [ $verschil -gt 3 ]; then

        # Stap 3: Check of de folder bestaat, zo niet --> aanmaken
        if [ ! -d "$year/$month/$week" ]; then
            mkdir -p "$year/$month/$week"
            echo "Folder $year/$month/$week aangemaakt"
        else
            echo "Folder $year/$month/$week bestaat al"
        fi

        # Stap 4: Kopieer het bestand
        cp "$f" "$year/$month/$week"
        new_file="$year/$month/$week/$f"
    fi


    # Stap 5: krijg de hash van beide fotos
    old_file=$f
    old_file_md5=($(md5sum "$1/$f"))
    new_file_md5=($(md5sum "$new_file"))

    # Stap 6: delete het origineel als de hash overeenkomt
    if [ "$old_file_md5" = "$new_file_md5" ]; then
        echo "De md5 vergelijking van $f klopt, de oude foto wordt verwijderd en als het er is wordt er overgegeaan op de volgende file"
        #rm "$1/$f"
        exit 1
    else
        echo "De md5 vergelijking van $f klopt niet, daarom wordt het programma geeindigd zonder een delete te doen"
        exit 1
    fi

done

