# 🚜 OOP Farm Simulator: Comparative Analysis

Projekt edukacyjny mający na celu porównanie implementacji paradygmatów **programowania obiektowego (OOP)** w trzech najpopularniejszych językach programowania: **C++**, **Java** oraz **Python**.

Symulator modeluje działanie gospodarstwa rolnego (hodowla zwierząt, uprawa roślin, zarządzanie zasobami), demonstrując różnice w składni, zarządzaniu pamięcią oraz strukturze klas.

## 🎯 Cel Projektu

Głównym celem była analiza porównawcza mechanizmów takich jak:
* **Dziedziczenie i Polimorfizm** (Inheritance & Polymorphism).
* **Enkapsulacja** (Encapsulation).
* **Zarządzanie pamięcią:** Ręczne (`delete` w C++) vs Automatyczne (Garbage Collection w Java/Python).

## 🛠️ Struktura i Technologie

Projekt składa się z trzech niezależnych modułów realizujących tę samą logikę biznesową:

### 1. Moduł C++ (`/cpp_version`)
* **Cechy:** Wykorzystanie wskaźników, wirtualnych destruktorów oraz ścisła kontrola typów.
* **Kluczowe zagadnienia:** Alokacja pamięci na stercie i stosie.

### 2. Moduł Java (`/java_version`)
* **Cechy:** Pełna obiektowość, wykorzystanie interfejsów i klas abstrakcyjnych.
* **Kluczowe zagadnienia:** Maszyna wirtualna JVM, automatyczne odśmiecanie pamięci.

### 3. Moduł Python (`/python_version`)
* **Cechy:** Dynamiczne typowanie, zwięzłość kodu ("Pythonic way").
* **Kluczowe zagadnienia:** `self`, brak ścisłych modyfikatorów dostępu (private/public).

## 🚀 Jak uruchomić

### C++
```bash
cd cpp_version
g++ main.cpp -o farm_sim
./farm_sim
```
### Java
```bash
cd java_version
javac Main.java
java Main
```
### Python
```bash
cd python_version
python3 main.py
