import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;

public class MessageTask extends Task {
    private String message;
    private String from;
    private String to;
    private LocalDateTime date;

    public static final DateTimeFormatter DATE_TIME_FORMATTER = DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm");

    public MessageTask(String taskID, String description, String message, String from, String to, LocalDateTime date) {
        super(taskID, description);
        this.message = message;
        this.from = from;
        this.to = to;
        this.date = date;
    }

    @Override
    public void execute() {
        System.out.println(date.format(DATE_TIME_FORMATTER) + ": " + message);
    }

    @Override
    public String toString() {
        return super.toString() + "|message=" + message + "|from=" + from + "|to=" + to + "|date=" + date.format(DATE_TIME_FORMATTER);
    }

    public String getMessage() { return message; }
    public String getFrom() { return from; }
    public String getTo() { return to; }
    public LocalDateTime getDate() { return date; }
}