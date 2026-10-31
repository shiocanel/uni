public class ExpressionEvaluator {
    public ComplexNumber evaluate(ComplexNumber[] numbers, Operation operation) {
        if (numbers == null || numbers.length == 0) {
            throw new IllegalArgumentException("Expresia nu contine numere!!!!!!!!!!!!!!!!!!!");
        }

        ComplexNumber result = numbers[0];
        for (int i = 1; i < numbers.length; i++) {
            result = operation.apply(result, numbers[i]);
        }

        return result;
    }
}
