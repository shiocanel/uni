package ex.functional;

public class Circle {
    private double radius;

    public Circle(double radius) {
        this.radius = radius;
    }

    public double getRadius() {
        return radius;
    }

    public static double area(Circle circle) {
        return Math.PI * Math.pow(circle.radius, 2);
    }
}
