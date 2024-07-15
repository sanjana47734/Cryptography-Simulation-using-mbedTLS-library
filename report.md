# Cryptography Simulation using mbedTLS Library

## Introduction
Cryptography is essential for securing data and communications in various applications. The mbedTLS library is a widely-used, open-source library designed to provide easy and secure cryptographic functionality for embedded systems and applications. This report covers the simulation of cryptographic operations using the mbedTLS library.

## Objectives
- To understand the basic concepts of cryptography.
- To implement cryptographic algorithms using the mbedTLS library.
- To simulate encryption and decryption processes.
- To explore the use of cryptographic hashing and digital signatures.

## Prerequisites
- Basic knowledge of C programming.
- Familiarity with cryptographic concepts such as encryption, decryption, hashing, and digital signatures.
- mbedTLS library installed.

## Setting Up the Environment
1. *Install mbedTLS Library:*
   ```sh
   git clone https://github.com/ARMmbed/mbedtls.git
   cd mbedtls
   mkdir build
   cd build
   cmake ..
   make
   sudo make install
   Create Your Project Directory:

mkdir ../my_crypto_simulation
cd ../my_crypto_simulation
Create a CMakeLists.txt File:

cmake
Copy code
cmake_minimum_required(VERSION 3.10)
project(CryptoSimulation)

set(CMAKE_C_STANDARD 99)

include_directories(../mbedtls/include)

add_executable(CryptoSimulation main.c)

target_link_libraries(CryptoSimulation 
    mbedcrypto
    mbedx509
    mbedtls
)
Explanation of the Code
The main.c file includes a simple example demonstrating AES (Advanced Encryption Standard) encryption and decryption using the mbedTLS library. Here is a breakdown of the steps:

Initialization:

Define a 32-byte key and a 16-byte input message.
Initialize the AES context using mbedtls_aes_init.
Encryption:

Set the encryption key using mbedtls_aes_setkey_enc.
Encrypt the input message using mbedtls_aes_crypt_ecb in ECB mode.
Print the encrypted output in hexadecimal format.
Decryption:

Set the decryption key using mbedtls_aes_setkey_dec.
Decrypt the encrypted message using mbedtls_aes_crypt_ecb.
Print the decrypted output as a string.
Conclusion
This report demonstrates how to set up and run a basic cryptography simulation using the mbedTLS library. The provided example focuses on AES encryption and decryption, which serves as a foundation for exploring more advanced cryptographic operations and protocols.

Feel free to expand this project by adding more features, such as different encryption algorithms, key management, or secure communication protocols.
