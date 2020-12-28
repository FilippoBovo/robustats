#!/usr/bin/env bash
# This formats the code to be (partially) PEP8 compliant.

# Sort imports
printf "Sorting the imports (isort).\n"
isort .

# Style the code
printf "\nStyling the code (black).\n"
black --line-length 120 .
