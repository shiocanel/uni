import java.lang.reflect.Array;
import java.util.*;

public class MyMap{
    private Map<Integer, List<Student>> map = new TreeMap<>();

    static class GradeComparator implements Comparator<Integer>{
        public int compare(Integer o1, Integer o2){
            return Float.compare(o2, o1);
        }
    }

    public MyMap(){
        map = new TreeMap<>(new GradeComparator());
    }

    public void add(Student student){
        int key = Math.round(student.getAverage());
        List<Student> list = null;
        if(!map.containsKey(key)){
            list = new ArrayList<>();
        }
        else{
            list = map.get(key);
        }

        list.add(student);
        map.put(key, list);
    }

    public Set<Map.Entry<Integer, List<Student>>> entrySet(){
        return map.entrySet();
    }


//    public void add(Student s){
//        List<Student> students;
//        if(map.containsKey(Math.round(s.getAverage()))){
//            students = map.get(Math.round(s.getAverage()));
//        }
//        else{
//            students = new ArrayList<Student>();
//        }
//
//        students.add(s);
//        students.sort(Comparator.comparing(Student::getAverage));
//
//
//        map.put(Math.round(s.getAverage()), students);
//    }


}
