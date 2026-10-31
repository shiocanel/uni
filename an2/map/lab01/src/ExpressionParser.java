public interface ExpressionParser {
    ComplexNumber[] parseNumbers(String[] arguments);
    String parseOperator(String[] arguments);
}
