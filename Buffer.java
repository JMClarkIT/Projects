package synchro;

public interface Buffer {
    void put(String value) throws InterruptedException;
    String get() throws InterruptedException;
}}
