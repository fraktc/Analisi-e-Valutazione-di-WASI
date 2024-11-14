#!/bin/bash

# Ensure prerequisites
if ! command -v wasmtime &> /dev/null; then
    echo "Error: 'wasmtime' command not found. Please install Wasmtime."
    exit 1
fi

if ! command -v node &> /dev/null; then
    echo "Error: 'node' command not found. Please install Node.js."
    exit 1
fi

# Ensure proper arguments
if [ $# -lt 3 ]; then
    echo "Error: Please provide at least a file pattern, the number of executions and the name of the file pattern."
    echo "Usage: $0 '*.pattern.wasm' 3"
    exit 1
fi

# output_pattern="$1"   # Example: "output_{runtime}.txt"

file_pattern="$1"
num_executions="$2"
file_pattern_name="$3"

# Define your list of runtimes
# runtimes=("wasmtime" "node" "wasmer_singlepass" "wasmer_cranelift" "wasmer_llvm" "wazero" "iwasm")  # Add more runtimes as needed
runtimes=("wasmedge")

# Iterates throug runtime , clear and create the output file
for runtime in "${runtimes[@]}"; do
    output_file="output_${runtime}_${file_pattern_name}.txt"
    > "$output_file"
done

# Iterate through files
for wasm_file in $file_pattern; do
    echo "Benchmarking file: $wasm_file"
    # Ensure we're dealing with a file
    if [ -f "$wasm_file" ]; then
        # Iterate through each runtime
        for runtime in "${runtimes[@]}"; do
            echo "Benchmarking runtime: $runtime"
            output_file="output_${runtime}_${file_pattern_name}.txt"
            # > "$output_file"  # Clear or create

            # echo "-----------------" >> "$output_file" 
            echo "$wasm_file" >> "$output_file"

            for i in $(seq 1 $num_executions); do
                echo "Executing $wasm_file (run $i/$num_executions):"

                if [ "$runtime" == "wasmtime" ]; then
                    wasmtime "$wasm_file" >> "$output_file" 2>&1
                elif [ "$runtime" == "node" ]; then
                    # Replace with your Node.js WASM execution logic
                    node --no-warnings execute_node.js "$wasm_file" >> "$output_file" 2>&1
                elif [ "$runtime" == "wasmer_singlepass" ]; then
                    wasmer run  "$wasm_file" --singlepass >> "$output_file" 2>&1
                elif [ "$runtime" == "wasmer_cranelift" ]; then
                    wasmer run  "$wasm_file" --cranelift >> "$output_file" 2>&1
                elif [ "$runtime" == "wasmer_llvm" ]; then
                    wasmer run  "$wasm_file" --llvm >> "$output_file" 2>&1
                elif [ "$runtime" == "wazero" ]; then
                    ~/bin/wazero run "$wasm_file" >> "$output_file" 2>&1
                elif [ "$runtime" == "iwasm" ]; then
                    ~/iwasm "$wasm_file" >> "$output_file" 2>&1
                    # ~/wasm-micro-runtime/product-mini/platforms/linux/build/iwasm "$wasm_file" >> "$output_file" 2>&1
		elif [ "$runtime" == "wasmedge" ]; then
		    wasmedge "$wasm_file" >> "$output_file" 2>&1
		else
                    echo "Unsupported runtime: $runtime" >> "$output_file"
                fi
            done
        done
    fi
done

echo "Execution results saved. Check files with pattern $output_pattern"
