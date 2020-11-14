#!/usr/bin/env bash
# # This is a shell script to synchronise the Python libraries with those in file requirements.txt.

if [ "$(pip freeze --exclude-editable)" != "$(cat requirements.txt)" ]
then
  printf "The installed libraries are not the same as those specified in file requirements.txt. ⚠️\n"
  read -r -p "Do you wish to synchronise the libraries? (y/n) " to_synchronise
  if [ "$to_synchronise" == "y" ]
  then
    printf "Synchronising libraries. 🔄\n"

    # Uninstall all the installed editable local packages
    printf "\nUninstalling all the installed editable local packages.\n"
    pip freeze | grep "#egg=" | xargs echo | sed -E 's/(.*)#egg=(.*)/\2/' | xargs pip uninstall -y

    # Uninstall all the installed libraries
    printf "\nUninstalling all the installed external libraries.\n"
    pip freeze --exclude-editable | xargs pip uninstall -y

    # Install the development requirements
    printf "\nInstalling the requirements.\n"
    pip install -r requirements.txt

    # Reinstall the local packages as editable
    printf "\nReinstalling the local packages as editable.\n"
    pip install --no-deps --editable .[dev]

    # Check that there are no conflicts between the installed libraries
    printf "\nChecking that there are no conflicts between the installed libraries.\n"
    pip check
  else
    printf "Synchronisation aborted. ❌\n"
  fi
fi
