package ex.functional;

import java.util.List;

public class Demo {
    public static <E> void printArea(List<E> figures, Area<E> area){
        for(E figure: figures){
            System.out.println(area.compute(figure));
        }
    }

    public static void main(String[] args) {
        List<Circle> circles = List.of(new Circle(4), new Circle(6), new Circle(5));

        System.out.println("Anonymous area");
        Area<Circle>anonymousCircle = new Area<Circle>(){
            public double compute(Circle circle){
                return Math.PI * circle.getRadius() * circle.getRadius();
            }
        };

        printArea(circles, anonymousCircle);

        System.out.println("Lambda Area");
        Area<Circle> lambaArea = c-> Math.PI * c.getRadius() * c.getRadius();
        printArea(circles, lambaArea);

        System.out.println("Reference Area");

        Area<Circle> refAre = Circle::area;
        printArea(circles, refAre);


        System.out.println("Square Area");
        List<Square> squares = List.of(new Square(4), new Square(6), new Square(5));
        printArea(squares, s->s.getSide() * s.getSide());
    }
}
