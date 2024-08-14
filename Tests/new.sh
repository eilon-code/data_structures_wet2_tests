rm -rf files/outputs
rm -rf files/inputs
rm -rf files/diffs
rm -rf files/my_out

# Prompt the user for input
read -p "Enter the number of tests: " test_count
read -p "Enter the number of lines per test file: " line_count
# Function to prompt for yes/no input
prompt_for_boolean() {
    while true; do
        read -p "$1 [Y/N]: " response
        case "$response" in
            [Yy]* ) echo "yes"; return 0;;  # Return 0 for yes
            [Nn]* ) echo "no"; return 1;;   # Return 1 for no
            * ) echo "Invalid input. Please enter 'Y' or 'N'.";;
        esac
    done
}

# Get interactive input
add_rank_tests=$(prompt_for_boolean "Does your code support adding rank tests?")

# Convert the boolean value to a format the Python script can handle
if [ "$add_rank_tests" = "yes" ]; then
    add_rank_tests="True"
else
    add_rank_tests="False"
fi

# Run the Python script with the provided inputs
python3 generate_tests.py "$test_count" "$line_count" "$add_rank_tests"
# ./run.sh