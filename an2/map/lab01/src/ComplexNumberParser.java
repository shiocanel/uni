public class ComplexNumberParser {
    public ComplexNumber parse(String text) {
        if (text == null || text.trim().length() == 0) {
            throw new IllegalArgumentException("Numarul complex nu poate fi gol.");
        }

        String value = text.replaceAll("\\s+", "").toLowerCase();
        if (!value.endsWith("i")) {
            return new ComplexNumber(parseReal(value), 0.0);
        }

        String coefficient = value.substring(0, value.length() - 1);
        if (coefficient.endsWith("*")) {
            coefficient = coefficient.substring(0, coefficient.length() - 1);
        }
        if (coefficient.length() == 0 || coefficient.equals("+")) {
            return new ComplexNumber(0.0, 1.0);
        }
        if (coefficient.equals("-")) {
            return new ComplexNumber(0.0, -1.0);
        }

        int separator = findRealImaginarySeparator(coefficient);
        if (separator < 0) {
            return new ComplexNumber(0.0, parseReal(coefficient));
        }

        String realPart = coefficient.substring(0, separator);
        String imaginaryPart = coefficient.substring(separator);

        if (imaginaryPart.equals("+"))
            imaginaryPart = "+1";
        if (imaginaryPart.equals("-"))
            imaginaryPart = "-1";
        return new ComplexNumber(parseReal(realPart), parseReal(imaginaryPart));
    }

    private int findRealImaginarySeparator(String value) {
        for (int i = 1; i < value.length(); i++) {
            char c = value.charAt(i);
            char previous = value.charAt(i - 1);
            if ((c == '+' || c == '-') && previous != 'e') return i;
        }
        return -1;
    }

    private double parseReal(String value) {
        try {
            return Double.parseDouble(value);
        }
        catch (NumberFormatException exception) {
            throw new IllegalArgumentException("Format invalid pentru numarul complex: " + value);
        }
    }
}
