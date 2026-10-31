import java.util.Objects;

public class Student implements Comparable<Student> {
    private String name;
    private float average;

    public Student(String name, float average) {
        this.name = name;
        this.average = average;
    }

    public String getName() {
        return name;
    }

    public float getAverage() {
        return average;
    }

    public String toString() {
        return name + " " + average;
    }

    @Override
    public boolean equals(Object obj) {
        if (obj instanceof Student) {
            Student s = (Student) obj;
            return this.name.equals(s.name) && this.average == s.average;
        }
        return false;
    }

    public int hashCode() {
        return Objects.hash(name, average);
    }

    @Override
    public int compareTo(Student o) {
        return this.name.compareTo(o.name);
    }
}
