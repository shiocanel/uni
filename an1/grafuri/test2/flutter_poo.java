class Student{
    String nume;
    int varsta;

    private String cnp;

    public void setCnp(String cnp){
        this.cnp = cnp;
    }

    public String getCnp(){
        return cnp;
    }

    void saluta(){
        System.out.println("Salut " + nume + " " + varsta);
    }
}

class Animal{
    void sunet(){
        System.out.println("Sunete de animal");
    }
}

class Dog extends Animal{

    @Override
    void sunet(){
        System.out.println("Sunet de caine!!");
    }
}

class Pisica extends Animal {

    @Override
    void sunet() {
        System.out.println("Miau");
    }
}




// interfete
interface Zburator {

    void zboara();
}

class Pasare implements Zburator{
    public void zboara(){
        System.out.println("Zboara o pasare");
    }
}

/**
 * flutter_poo
 */
public class flutter_poo {

    public static void main(String[] args) {
        Student s = new Student();
        s.nume = "Ion";
        s.varsta = 19;

        s.saluta();

        Animal d = new Dog();
        d.sunet();

        Integer[] a = new Integer[20];
        for(int i = 0; i < 10; i++)
            a[i] = i;

        for(int i = 0; i < 10; i++)
            System.out.println(a[i]);
    }
}