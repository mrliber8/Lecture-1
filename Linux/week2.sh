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


# Stap 2: Krijg de tijden van de file
BASE_DIR="/home/liber8"="/mnt/c/Users/patrick/Downloads/Lecture 1 Demo code(2)/Lecture 1/Linux"
echo $BASE_DIR
cd $BASE_DIR

for f in *.png do
    ## Krijg de jaar tijden van de file
    year="$(date -d "$(stat -c %y "$f")" +%Y)"
    ## Krijg de maand tijden van de file
    month="$(date -d "$(stat -c %y "$f")" +%B)"
    ## Krijg de week tijden van de file
    week="$(date -d "$(stat -c %y "$f")" +%U)"

    if [ $2 == "maand" ]; then

        # Stap 3: Check of de folder bestaat, zo niet --> aanmaken
        if [! -d "$BASE_DIR/$year/$month"]; then
            mkdir "$BASE_DIR/$year/$month"
        fi

        # Stap 4: Kopieer het bestand
        cp "$f" "$BASE_DIR/$year/$month"
        new_file="$BASE_DIR/$year/$month/$f"

    elif [ $2 == "week" ]; then

        # Stap 3: Check of de folder bestaat, zo niet --> aanmaken
        if [! -d "$BASE_DIR/$year/$month/$week"]; then
            mkdir "$BASE_DIR/$year/$month/$week"
        fi

        # Stap 4: Kopieer het bestand
        cp "$f" "$BASE_DIR/$year/$month/$week"
        new_file="$BASE_DIR/$year/$month/$week/$f"
    fi



# Stap 5: krijg de hash van beide fotos
# Stap 6: delete het origineel als de hash overeenkomt

