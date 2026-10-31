public class OperationFactory {
    public Operation create(String symbol) {
        if ("+".equals(symbol)) return new AddOperation();
        if ("-".equals(symbol)) return new SubtractOperation();
        if ("*".equals(symbol)) return new MultiplyOperation();
        if ("/".equals(symbol)) return new DivideOperation();
        throw new IllegalArgumentException("Operator necunoscut: " + symbol);
    }
}
