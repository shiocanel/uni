Laborator 01

Programul primeste prin argumentele liniei de comanda o expresie cu numere complexe, in forma:
numar operator numar [operator numar ...]
Operatorul este acelasi intre toti termenii

java Main "2 + 3*i" + "5 - 6*i" + "-2 + i"
Rezultat: 5.0 - 2.0*i

Validare si comportament
    - Expresia trebuie sa contina un numar impar de argumente: numar, operator, numar, ...
    - Sunt acceptati operatorii +, -, * si /
    - Toate operatiile dintre termeni trebuie sa foloseasca acelasi operator
    - Impartirea la zero complex produce mesaj de eroare.
    - Pentru expresii cu mai multi termeni, evaluarea se face de la stanga la dreapta

Proiectare OOP si principii SOLID
    - Single Responsibility Principle (SRP):
        ComplexNumber modeleaza si calculeaza operatii pentru un numar complex;
        ComplexNumberParser parseaza un numar;
        CommandLineExpressionParser valideaza structura argumentelor;
        ExpressionEvaluator evalueaza expresia;
        fiecare clasa Operation implementeaza o operatie;
        Main coordoneaza aplicatia.
    - Open/Closed Principle (OCP):
        se poate adauga o noua operatie printr-o noua implementare a interfetei Operation. Pentru o extindere complet deschisa,
        fabrica poate fi ulterior inlocuita cu o inregistrare configurabila a operatiilor
    - Liskov Substitution Principle (LSP):
        orice implementare Operation poate fi folosita de ExpressionEvaluator fara schimbarea acestuia
    - Interface Segregation Principle (ISP):
        interfetele Operation si ExpressionParser sunt mici si contin doar metodele necesare clientilor lor
    - Dependency Inversion Principle (DIP):
        ExpressionEvaluator depinde de abstractizarea Operation, iar coordonarea foloseste interfata ExpressionParser;
        nu are nevoie sa cunoasca clasele concrete de operatie.

Sablon de proiectare
    - Strategy: AddOperation, SubtractOperation, MultiplyOperation si DivideOperation sunt strategii interschimbabile prin interfata Operation.
    - Simple Factory: OperationFactory centralizeaza selectarea implementarii concrete pe baza simbolului operatorului.

Clase si responsabilitati
    - ComplexNumber: model de domeniu imuabil; pastreaza partea reala si imaginara si implementeaza calculele.
    - ComplexNumberParser: transforma textul intr-un ComplexNumber.
    - ExpressionParser: contract pentru parsarea expresiei din argumente.
    - CommandLineExpressionParser: valideaza structura si extrage numerele/operatorul.
    - Operation: contract pentru strategiile aritmetice.
    - AddOperation / SubtractOperation / MultiplyOperation / DivideOperation: operatii concrete.
    - OperationFactory: creeaza strategia potrivita.
    - ExpressionEvaluator: calculeaza rezultatul aplicand strategia asupra termenilor.
    - Main: punct de intrare, conecteaza componentele si trateaza erorile de intrare.

Conformitate cu restrictiile
Implementarea foloseste tablouri simple, nu foloseste colectii generice, streams, lambda expressions sau API-uri Java 8.
Codul este scris cu sintaxa compatibila cu versiuni Java anterioare Java 8.
