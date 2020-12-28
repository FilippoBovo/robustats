#!/usr/bin/env bash
# This shell script checks that the code complies with PEP 8 and that the Python types are consistent.
BOLD_TEXT=$(tput bold)
NORMAL_TEXT=$(tput sgr0)

EXIT_STATUS=0

# Validate the imports with isort
printf "Validating the imports with Isort.\n"
isort --check-only .
if [ $? -ne 0 ]
then
  EXIT_STATUS=1
fi

# Validate the code with Black
printf "\nValidating the code format with Black.\n"
black --check --line-length 120 .
if [ $? -ne 0 ]
then
  EXIT_STATUS=1
fi

# Check that the code complies with the PEP8 code standards
printf "\nChecking that the code complies with the PEP8 code standards with Flake8.\n"
flake8 .
if [ $? -ne 0 ]
then
  EXIT_STATUS=1
fi

# Check that the Python types are consistent
printf "\nChecking that the Python types are consistent with Mypy.\n"
mypy .
if [ $? -ne 0 ]
then
  EXIT_STATUS=1
fi

# Exit with status 1 if there are issues found in the code, otherwise exit with status 0
if [ $EXIT_STATUS -eq 0 ]
then
  printf "\n%sNO ISSUES FOUND IN CODE - ALL GOOD!%s ✅\n" "$BOLD_TEXT" "$NORMAL_TEXT"
  exit 0
else
  printf "\n%sISSUES FOUND IN CODE - PLEASE REVIEW!%s ❌\n" "$BOLD_TEXT" "$NORMAL_TEXT"
  exit 1
fi
