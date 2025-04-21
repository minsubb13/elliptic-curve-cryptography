#include <random>

#include "elliptic_curve.h"
#include "ECDH.h"
#include "breakingDLP/bruteforce.h"
#include "breakingDLP/baby_giant_step.h"
#include "breakingDLP/pollard_rho.h"

void print_header(const std::string& title) {
    std::cout << "\n" << std::string(50, '=') << std::endl;
    std::cout << "  " << title << std::endl;
    std::cout << std::string(50, '=') << std::endl;
}

void test_modular_arithmetic() {
    print_header("Test Modular Arithmetic");

    long long p;
    std::cout << "Input prime : ";
    std::cin >> p;
    ModularArithmetic mod(p);

    std::cout << "modulus: " << p << std::endl;
    std::cout << "15 + 14 mod " << p << " = " << mod.add(15, 14) << std::endl;
    std::cout << "7 - 10 mod " << p << " = " << mod.subtract(7, 10) << std::endl;
    std::cout << "3 * 5 mod " << p << " = " << mod.multi(3, 5) << std::endl;
    std::cout << "2^8 mod " << p << " = " << mod.power(2, 8) << std::endl;

    for (int a = 1; a < p; a++) {
        long long result = mod.power(a, p - 1);
        if (result != 1) {
            std::cout << "Failed Fermat's little Theorem: " << a << "^(" << p-1 << ") mod "
                      << p << " = " << result << " ≠ 1" << std::endl;
        }
    }
    std::cout << "Fermat's little Theorem verfication completed" << std::endl;
}

void test_elliptic_curve() {
    print_header("Test Elliptic Curve Operations");

    ModularArithmetic Fp(97);
    Point g(3, 6);
    EllipticCurve curve(
        Fp,
        2,
        3,
        g,
        100
    );

    long long order = curve.get_order();

    std::cout << "Elliptic Curve: " << curve.toString() << std::endl;
    std::cout << "g : (" << g.x << ", " << g.y << ")" << std::endl;
    std::cout << "Cyclic subgroup order (n) : " << order << std::endl;
    std::cout << std::endl;

    Point P(17, 10);
    Point Q(95, 31);
    Point add_result = curve.add(P, Q);

    std::cout << "Point P : (" << P.x << ", " << P.y << ")" << std::endl;
    std::cout << "Point Q : (" << Q.x << ", " << Q.y << ")" << std::endl;
    std::cout << "P + Q = (" << add_result.x << ", " << add_result.y << ")" << std::endl;

    Point double_p = curve.doublePoint(P);
    std::cout << "2P = (" << double_p.x << ", " << double_p.y << ")" << std::endl;

    long long scalar;
    std::cout << "Input scalar n: ";
    std::cin >> scalar;
    Point multi_point = curve.scalar_multi(scalar, P);
    std::cout << "nP = (" << multi_point.x << ", " << multi_point.y << ")" << std::endl;
}

void test_ecdh() {
    print_header("Test ECDH Key Exchange");

    ModularArithmetic Fp(10177);
    Point g(1, 1);
    EllipticCurve curve(
        Fp,
        1,
        -1,
        g,
        10331
    );
    long long order = curve.get_order();

    std::cout << "Elliptic Curve: " << curve.toString() << std::endl;
    std::cout << "g : (" << g.x << ", " << g.y << ")" << std::endl;
    std::cout << "Cyclic subgroup order (n) : " << order << std::endl;
    std::cout << std::endl;

    auto [Alice_private_key, Alice_public_key] = make_keypair(curve);
    auto [Bob_private_key, Bob_public_key] = make_keypair(curve);

    std::cout << "Alice's private key : "  << Alice_private_key << std::endl;
    std::cout << "Alice's public key: (" << Alice_public_key.x
              << ", " << Alice_public_key.y << ")" << std::endl;

    std::cout << "Bob's private key : " << Bob_private_key << std::endl;
    std::cout << "Bob's public key: (" << Bob_public_key.x
              << ", " << Bob_public_key.y << ")" << std::endl;

    Point alice_shared_secret = curve.scalar_multi(Alice_private_key, Bob_public_key);
    Point bob_shared_secret = curve.scalar_multi(Bob_private_key, Alice_public_key);
    std::cout << "Alice's shared secret: (" << alice_shared_secret.x << ", "
              << alice_shared_secret.y << ")" << std::dec << std::endl;
    std::cout << "Bob's shared secret: (" << bob_shared_secret.x << ", "
              << bob_shared_secret.y << ")" << std::dec << std::endl;
    std::cout << "Do Alice's and Bob's shared secrets match? "
              << (alice_shared_secret.x == bob_shared_secret.x 
                  && alice_shared_secret.y == bob_shared_secret.y 
                  ? "Yes" : "No") << std::endl;
}

void test_dlp_solvers() {
    print_header("Testing Discrete Logarithm Problem Solvers");

    ModularArithmetic Fp(10177);
    Point g(1, 1);
    EllipticCurve curve(
        Fp,
        1,
        -1,
        g,
        10331
    );
    long long order = curve.get_order();
    Point generator = curve.get_generator();

    std::cout << "Elliptic Curve: " << curve.toString() << std::endl;
    std::cout << "g : (" << g.x << ", " << g.y << ")" << std::endl;
    std::cout << "Cyclic subgroup order (n) : " << order << std::endl;
    std::cout << std::endl;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<long long> dis(0, order);

    std::cout << '\n';
    std::cout << "Creating point P, Q and integer x such that Q = xP" << std::endl;
    long long x = dis(gen);
    Point P = generator;
    Point Q = curve.scalar_multi(x, P);
    std::cout << "P : (" << P.x << ", " << P.y << ")" << std::endl;
    std::cout << "Q : (" << Q.x << ", " << Q.y << ")" << std::endl;
    std::cout << "x : "<< x << std::endl;

    std::cout << '\n';
    std::cout << "Test 1: Brute Force" << std::endl;
    auto bruteforce = BruteForce(curve, P, Q);
    std::cout << "log(P, Q) = " << std::get<0>(bruteforce) << std::endl;
    std::cout << "Took " << std::get<1>(bruteforce) << " steps" << std::endl;

    std::cout << '\n';
    std::cout << "Test 2: The Baby-step Giant-step" << std::endl;
    auto Baby_Giant_step = Babystep_Giantstep(curve, P, Q);
    std::cout << "log(P, Q) = " << std::get<0>(Baby_Giant_step) << std::endl;
    std::cout << "Took " << std::get<1>(Baby_Giant_step) << " steps" << std::endl;

    std::cout << '\n';
    std::cout << "Test 3: Pollard's rho" << std::endl;
    auto pollards_rho = pollard_rho(curve, P, Q);
    std::cout << "log(P, Q) = " << std::get<0>(pollards_rho) << std::endl;
    std::cout << "Took " << std::get<1>(pollards_rho) << " steps" << std::endl;
}

void print_help() {
    print_header("ECC Test Program Usage Guide");
    std::cout << "./ecc_program [command]" << std::endl;
    std::cout << "command:" << std::endl;
    std::cout << "  help           - Display help information" << std::endl;
    std::cout << "  all            - Run all tests" << std::endl;
    std::cout << "  arithmetic     - Test modular arithmetic operations" << std::endl;
    std::cout << "  curve          - Test elliptic curve operations" << std::endl;
    std::cout << "  ecdh           - Test ECDH key exchange" << std::endl;
    std::cout << "  dlp            - Test discrete logarithm problem solvers" << std::endl;
}

int main(int argc, char* argv[]) {
    std::cout << "Elliptic Curve Cryptography Test Program" << std::endl;
    
    if (argc < 2) {
        print_help();
        return 0;
    }

    std::string command = argv[1];

    if (command == "help") {
        print_help();
    }
    else if (command == "all") {
        test_modular_arithmetic();
        test_elliptic_curve();
        test_ecdh();
        test_dlp_solvers();
    }
    else if (command == "arithmetic") {
        test_modular_arithmetic();
    }
    else if (command == "curve") {
        test_elliptic_curve();
    }
    else if (command == "ecdh") {
        test_ecdh();
    }
    else if (command == "dlp") {
        test_dlp_solvers();
    }
    else {
        std::cout << "Unknown command: " << command << std::endl;
        print_help();
        return 1;
    }

    return 0;
}