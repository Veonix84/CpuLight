package com.veonix.cpulight;

import jssc.SerialPort;
import org.hyperic.sigar.Sigar;

import java.io.File;
import java.io.FileInputStream;
import java.util.Properties;

public class CpuLight extends Thread {

    private String comPort;
    private long sleepTime;

    private Sigar sigar;
    private SerialPort serialPort;

    private boolean isRunning;

    public void init() throws Exception {
        Properties properties = new Properties();

        File file = new File("application.properties");
        if(file.exists()) {
            properties.load(new FileInputStream(file));
        }

        comPort = properties.getProperty("comPort", "COM3");
        sleepTime = Long.parseLong(properties.getProperty("sleepTime", "1000"));

        sigar = new Sigar();

        serialPort = new SerialPort(comPort);
        serialPort.openPort();
        serialPort.setParams(
                SerialPort.BAUDRATE_9600,
                SerialPort.DATABITS_8,
                SerialPort.STOPBITS_1,
                SerialPort.PARITY_NONE);

        serialPort.setRTS(false);
        serialPort.setDTR(false);
    }

    public void close() throws Exception {
        if(sigar != null) {
            sigar.close();
        }
        if(serialPort != null && serialPort.isOpened()) {
            serialPort.closePort();
        }
    }

    public void shutdown() {
        this.isRunning = false;
    }

    @Override
    public void run() {
        try {
            execute();
        }
        catch(Exception ex) {
            throw new RuntimeException(ex);
        }
    }

    public void execute() throws Exception {
        Thread.sleep(500);

        isRunning = true;

        while(isRunning) {
            double rawCpu = sigar.getCpuPerc().getCombined();
            int cpu = (int)Math.round(rawCpu*100);
            byte value = (byte)(cpu*2);

            System.out.println(cpu + "%");

            serialPort.writeByte(value);

            Thread.sleep(sleepTime);
        }
    }
}
