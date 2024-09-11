import subprocess
import os

def run_cpp_file():
    # Compile the C++ code
    cpp_filename = 'deque_test.cpp'
    compile_process = subprocess.run(["g++", "-std=c++11", cpp_filename, "-o", "temp_executable"], stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)

    # Check for compilation errors
    if compile_process.returncode != 0:
        print("Compilation error:")
        print(compile_process.stderr)
        return

    # Run the compiled executable
    run_process = subprocess.run(["./temp_executable"], stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True, timeout=10)

    print(run_process.stdout)
    
    valgrind_cmd = ["leaks", "--atExit", "--", "./temp_executable"]

    try:
        process = subprocess.Popen(valgrind_cmd, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        stdout, stderr = process.communicate(20)
        
        if "0 leaks for 0 total leaked bytes" not in stderr.decode():
            print("Valgrind detected memory leaks")
        else:
            print("No memory leaks detected")
    except subprocess.CalledProcessError as e:
        print("Valgrind error") 

    if(run_process.stderr):
        print("Error:")
        print(run_process.stderr) 
    
    try:
        os.remove("./temp_executable")
    except FileNotFoundError:
        print("Compilation error")

run_cpp_file()
