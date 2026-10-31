public class CommandLineExpressionParser implements ExpressionParser {
    private final ComplexNumberParser numberParser;

    public CommandLineExpressionParser(ComplexNumberParser numberParser) {
        this.numberParser = numberParser;
    }

    public ComplexNumber[] parseNumbers(String[] arguments) {
        validateShape(arguments);
        int numberCount = (arguments.length + 1) / 2;
        ComplexNumber[] numbers = new ComplexNumber[numberCount];

        for (int i = 0; i < arguments.length; i += 2) {
            numbers[i / 2] = numberParser.parse(arguments[i]);
        }
        return numbers;
    }

    public String parseOperator(String[] arguments) {
        validateShape(arguments);
        String operator = arguments[1];
        if (!("+".equals(operator) || "-".equals(operator) || "*".equals(operator) || "/".equals(operator))) {
            throw new IllegalArgumentException("Operator invalid: " + operator);
        }
        for (int i = 1; i < arguments.length; i += 2) {
            if (!operator.equals(arguments[i])) {
                throw new IllegalArgumentException("Toate operatiile dintre numere trebuie sa foloseasca acelasi operator");
            }
        }
        return operator;
    }

    private void validateShape(String[] arguments) {
        if (arguments == null || arguments.length < 3 || arguments.length % 2 == 0) {
            throw new IllegalArgumentException("Expresia trebuie sa aiba forma: numar operator numar ...");
        }
    }
}
