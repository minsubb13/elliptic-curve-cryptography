# Elliptic Curve Cryptography

This repository contains C++ implmentations of Elliptic Curve Cryptography (ECC) for educational purposes.

This code is based on the blog post series [Elliptic Curve Cryptography: a gentle introduction](http://andrea.corbellini.name/2015/05/17/elliptic-curve-cryptography-a-gentle-introduction/)

## Features
- Test modular arithmetic operations
- Explorer basic functions of elliptic curves
- Perform ECDH (Elliptic Curve Diffie-Hellman) key exchange
- Calcualte solutions to the discrete logarithm problem (DLP)

## Getting started

1. Clone the repository and navigate to the project directory:
   ```
   $ git clone https://github.com/minsubb13/ECC.git
   $ cd ECC/
   ```

2. Complie the code:
    
    ```
    $ make
    ```

3. Run the program with all cases:

    ```
    $ ./ecc all
    ```

### Help
For additional commands and options, use the help command:
```
$ ./ecc help
```



## TODO

- Implementation of big number library (like `GMP`, `BIGNUM`)

- Implementation to Rust
