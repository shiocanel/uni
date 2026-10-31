public final class ComplexNumber {
    private final double real;
    private final double imaginary;

    public ComplexNumber(double real, double imaginary) { // OKKKKK
        this.real = real;
        this.imaginary = imaginary;
    }

    public double getReal() { return real; }
    public double getImaginary() { return imaginary; }

    public ComplexNumber add(ComplexNumber other) {
        return new ComplexNumber(real + other.real, imaginary + other.imaginary);
    }

    public ComplexNumber subtract(ComplexNumber other) {
        return new ComplexNumber(real - other.real, imaginary - other.imaginary);
    }

    public ComplexNumber multiply(ComplexNumber other) {
        return new ComplexNumber(real * other.real - imaginary * other.imaginary,
                real * other.imaginary + imaginary * other.real);
    }

    public ComplexNumber divide(ComplexNumber other) {
        double denominator = other.real * other.real + other.imaginary * other.imaginary;
        if (denominator == 0.0) {
            throw new IllegalArgumentException("Impartirea la 0!!!!!");
        }
        return new ComplexNumber((real * other.real + imaginary * other.imaginary) / denominator,
                (imaginary * other.real - real * other.imaginary) / denominator);
    }

    @Override
    public String toString() {
        double r = cleanZero(real);
        double im = cleanZero(imaginary);
        if (im < 0)
            return r + " - " + Math.abs(im) + "*i";
        return r + " + " + im + "*i";
    }

    private double cleanZero(double value) {
        return Math.abs(value) < 1.0E-10 ? 0.0 : value;
    }
}
