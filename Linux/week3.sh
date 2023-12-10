#!/bin/sh

# In de file apache-access-log.txt vind je een access-log.
# Schrijf een regex die mailadressen herkent van het bedrijf “shaw”. Het bedrijf staat zowel
# onder de tld com en .net geregistreerd.

# In de basis volgt het bedrijf Shaw de conventies van email-naamgeving van RFC 822.
# Daarboven op hebben ze de volgende naamgevingssystemetiek. 
#   -	Generieke opbouw van een mailadres bij Shaw is: <mailnaam>@shaw.com of <mailnaam>@shaw.net
#   -	Voor de <mailnaam> geldt:
#       o	Minimaal 2 karakters (karakter= cijfer, letter en speciale tekens), maximaal 99
#       o	Op laatste positie staat of een letter (“a” t/m “z” , “A” t/m “Z”), of een cijfer(“0” t/m “9”)
#       o	Op andere posities geen cijfers toegestaan, wel letters of de speciale tekens “.”, “_” en “-“
#       o	Andere speciale tekens geheel niet toegestaan

# De regex kun je als volgt controleren:
# grep -E -o "<YOUR_REGEX>" access_log


# Eerste is hofdletter tweede is kleine:
# [A-Z][a-z]

# Minimaal 1x a maar max 3a
# a{1,3}

# 5 characters, elke hiervan kan w, x of y zijn
# [wxy]{5}

# Min 2 en max 6 van elk character
# .{2,6}

# 1 of meer a
# a+

# 1 of meer van de characters a,b of c
# [abc]+

# niks of meer van elke character
# .*

# Matcht voor abc of ac want b wordt als optioneel gezien
# ab?c

# Match voor whitespace zoals \t, \n, \r of gewoone en spatie
# \s+

# Start met Mission: en eindigt met successful
# ^Mission: successful$ 

# Matches cats or bats OR dogs or hogs
# ([cb]ats*|[dh]ogs?)


# Eerste draft

#       o	Op laatste positie staat of een letter (“a” t/m “z” , “A” t/m “Z”), of een cijfer(“0” t/m “9”)
#       o	Op andere posities geen cijfers toegestaan, wel letters of de speciale tekens “.”, “_” en “-“

# Op laatste positie staat of een letter (“a” t/m “z” , “A” t/m “Z”), of een cijfer(“0” t/m “9”)
# [a-zA-Z0-9]

# Op andere posities geen cijfers toegestaan, wel letters of de speciale tekens “.”, “_” en “-“
# [a-zA-Z\._-]

# Min 2, laatste mag alleen leter of cijfer zijn, Max is 99 min de laatste is 98
# Dus minimaal 1 om op de twee te komen en max 98
# [a-zA-Z\._-]{1,98}

# Het bedrijf staat zowel onder de tld com en .net geregistreerd.
# Het kan eindigen op shaw.com of shaw.net
# @(shaw\.com|shaw\.net) 

# Samengevoegd
grep -E -o "[a-zA-Z\._-]{1,98}[a-zA-Z0-9]@(shaw\.com|shaw\.net)" access_log.txt

# Antwoord als je dit uitvoert:
# ppwctwentynine@shaw.com




