public class Main {
    public static void main(String[] args) {
        try {
            ExpressionParser parser = new CommandLineExpressionParser(new ComplexNumberParser());
            String symbol = parser.parseOperator(args);

            ComplexNumber[] numbers = parser.parseNumbers(args);
            Operation operation = new OperationFactory().create(symbol);

            ComplexNumber result = new ExpressionEvaluator().evaluate(numbers, operation);
            System.out.println(result);
        }
        catch (IllegalArgumentException exception) {
            System.err.println("Eroare: " + exception.getMessage());
            System.err.println("Exemplu: java Main \"2 + 3*i\" + \"5 - 6*i\" + \"-2 + i\"");
            System.exit(1);
        }
    }
}
