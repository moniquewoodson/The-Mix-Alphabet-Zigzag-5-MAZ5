//Algorithm Name: The Mix Alphabet Zigzag 5 (MAZ5)
#include<iostream>
#include<string>
#include<algorithm>
using namespace std;

//The Different Keys
int key_caesar = 5;
int key_caesar2 = 2;
int key_rail = 3;

// Define the encryption function
string encrypt(string plaintext)
{
    //Apply Substition to the Plaintext
    string ciphertext = "";
    for (int i = 0; i < plaintext.length(); i++)
    {
        if (isupper(plaintext[i]))
            ciphertext += char(int(plaintext[i] + key_caesar - 65) % 26 + 65);
    }

    // Apply Transposition to the ciphertext
    int row = key_rail, col = ciphertext.length();
    char rail[row][col];
    for (int i = 0; i < row; i++)
        for (int j = 0; j < col; j++)
            rail[i][j] = '\n';
    bool dir_down;
    int row_curr = 0, col_curr = 0;
    for (int i = 0; i < col; i++)
    {
        if (row_curr == 0)
            dir_down = true;
        if (row_curr == row - 1)
            dir_down = false;
        rail[row_curr][col_curr++] = ciphertext[i];
        dir_down ? row_curr++ : row_curr--;
    }
    string result;
    for (int i = 0; i < row; i++)
        for (int j = 0; j < col; j++)
            if (rail[i][j] != '\n')
                result.push_back(rail[i][j]);
    return result;
}

// Define the decryption function
string decrypt(string ciphertext)
{
    // Apply inverse Transposition to the ciphertext
    int row = key_rail, col = ciphertext.length();
    char rail[row][col];
    for (int i = 0; i < row; i++)
        for (int j = 0; j < col; j++)
            rail[i][j] = '\n';
    bool dir_down;
    int row_curr = 0, col_curr = 0;
    for (int i = 0; i < col; i++)
    {
        if (row_curr == 0)
            dir_down = true;
        if (row_curr == row - 1)
            dir_down = false;
        rail[row_curr][col_curr++] = '*';
        dir_down ? row_curr++ : row_curr--;
    }
    int index = 0;
    for (int i = 0; i < row; i++)
        for (int j = 0; j < col; j++)
            if (rail[i][j] == '*' && index < col)
                rail[i][j] = ciphertext[index++];
    string result2;
    row_curr = 0, col_curr = 0;
    for (int i = 0; i < col; i++)
    {
        if (row_curr == 0)
            dir_down = true;
        if (row_curr == row - 1)
            dir_down = false;
        if (rail[row_curr][col_curr] != '*')
            result2.push_back(rail[row_curr][col_curr++]);
        dir_down ? row_curr++ : row_curr--;
    }

    //Apply inverse Substitution to the ciphertext
    string plaintext = "";
    for (int i = 0; i < result2.length(); i++)
    {
        if (isupper(result2[i]))
            plaintext += char(int(result2[i] - key_caesar2 - 65 + 26) % 26 + 65);
    }
    return plaintext;
}

//The main function
int main()
{
  // Get the input message
    string message;
    cout << "Enter the plaintext (IN ALL CAPS): ";
    getline(cin, message);

  //Encrypt the message 
    string encryted_message = encrypt(message);
    cout << "Encrypted Text: " << encryted_message << endl;
  
  //Decrypt the message
    string decryted_message = decrypt(message);
    cout << "Decrypted Text: " << decryted_message << endl;

    return 0;
}