import java.util.*;

public class Main {
    public static List<Student> getList() {
        List<Student> l = new ArrayList<Student>();
        l.add(new Student("ana", 9.7f));
        l.add(new Student("bob", 7.3f));
        l.add(new Student("mata", 6f));
        l.add(new Student("ion", 6.9f));
        l.add(new Student("vanea", 9.5f));
        l.add(new Student("grigore", 9.9f));
        return l;
    }

    public static void main(String[] args) {
        Student s1 = new Student("Dan", 4.5f);
        Student s2 = new Student("Ana", 8.5f);
        Student s3 = new Student("Dan", 4.5f);

        System.out.println(s1.equals(s3));
        System.out.println(s1.hashCode());
        System.out.println(s3.hashCode());

        System.out.println("==HashSet==");

        Set<Student> students = new HashSet<>();
        students.add(s1);
        students.add(s2);
        students.add(s3);

        System.out.println(students.size());

        System.out.println("==TreeSet==");

        Set<Student> treeSet = new TreeSet<>();
        treeSet.add(s1);
        treeSet.add(s2);
        treeSet.add(s3);

        for (Student student : treeSet) {
            System.out.println(student);
        }

        System.out.println("==Tree Set Comparator==");
        Comparator<Student> comparator = new Comparator<Student>() {
            @Override
            public int compare(Student o1, Student o2) {
                return Float.compare(o2.getAverage(), o1.getAverage());
            }
        };

        Set<Student> setWithComparator = new TreeSet<>(comparator);
        setWithComparator.add(s1);
        setWithComparator.add(s2);
        setWithComparator.add(s3);

        for(Student student : setWithComparator) {
            System.out.println(student);
        }

        System.out.println("==HashMap==");
        Map<String, Student> map = new HashMap<>();
        map.put(s1.getName(), s1);
        map.put(s2.getName(), s2);
        map.put(s3.getName(), s3);

        System.out.println(map.size());
        for (Map.Entry<String, Student> entry : map.entrySet()) {
            System.out.println(entry.getValue());
            System.out.println(entry.getKey());
        }

        System.out.println("==Tree Map==");
        Map<String, Student> treeMap = new HashMap<>();
        treeMap.put(s1.getName(), s1);
        treeMap.put(s2.getName(), s2);
        treeMap.put(s3.getName(), s3);

        for (Map.Entry<String, Student> entry : treeMap.entrySet()) {
            System.out.println(entry.getValue());
            System.out.println(entry.getKey());
        }

        System.out.println("==List==");
        List<Student> list = new ArrayList<>();
        list.add(s1);
        list.add(s2);
        list.add(s3);
        Iterator<Student> iterator = list.iterator();

        while (iterator.hasNext()){
            Student student = iterator.next();
            System.out.println(student);
        }

        MyMap myMap = new MyMap();
        List<Student> lista = getList();
        for(Student student : lista){
            myMap.add(student);
        }

        for(Map.Entry<Integer, List<Student>> entry : myMap.entrySet()){
            System.out.println(entry.getKey());
            for (Student student : entry.getValue()){
                System.out.println(student);
            }
        }
    }
}