# Synonymw: Word Prediction using a Recurrent Neural Network

Synonymw is a C++ project that demonstrates word prediction by finding the nearest synonym for a given word. It uses a simple recurrent neural network (RNN) trained on a provided dataset of word pairs.

## How It Works

The program implements a character-level "vanilla" RNN to learn associations between words. Here's a high-level overview of the process:

1.  **Data Loading**: The program reads word pairs (e.g., "happy joyful") from a data file.
2.  **Tokenization & Vocabulary**: It builds a vocabulary of all unique words from the dataset.
3.  **One-Hot Encoding**: Each word is converted into a numerical vector format (one-hot encoding) that can be fed into the neural network.
4.  **Training**: The RNN is trained on the input-target pairs for a fixed number of iterations (10,000 in the current implementation). The model learns the relationships between the words.
5.  **Prediction**: After training, the model can predict the synonym for a given input word.

## How to Build and Run

This is a Windows console application written in C++. To build and run it, you will need a C++ compiler like g++ or the Visual Studio compiler.

1.  **Compile the code**:
    ```bash
    g++ source/main.cpp -o Synonymw.exe
    ```
2.  **Prepare the data file**: Make sure the training data file, `Test_Data.txt`, is in the same directory as the executable.
3.  **Run the executable**:
    ```bash
    ./Synonymw.exe
    ```
    The program will then train the model and print the predicted synonyms for the input words from the data file.

## Data Format

The training data should be a text file where each line contains a pair of words separated by a space. The first word is the input, and the second is the target synonym.

Example (`Test_Data.txt`):
```
happy joyful
sad unhappy
fast quick
```

## Known Issues

*   **Hardcoded File Path**: The file `source/main.cpp` contains a hardcoded absolute path to the data file: `E:\\Dhruv\\Vanilla2\\Test.txt`. This will cause the program to fail if that path doesn't exist. For the program to work correctly, you should modify this line in `main.cpp` to point to the `Test_Data.txt` file in the project directory. A future improvement would be to allow the user to specify the data file path as a command-line argument.
