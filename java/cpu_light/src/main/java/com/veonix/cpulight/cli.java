package com.veonix.cpulight;

import java.io.BufferedReader;
import java.io.InputStreamReader;

public class cli
{
    public static void main(String[] args) throws Exception
    {
        CpuLight cpuLight = null;

        try {
            cpuLight = new CpuLight();
            cpuLight.init();

            cpuLight.start();

            BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
            String line = "";

            while(!line.equalsIgnoreCase("q")) {
                line = in.readLine();
                System.out.println(line);
            }

            in.close();

            cpuLight.shutdown();
            while(cpuLight.isAlive()) {
                Thread.sleep(250);
            }
        }
        finally {
            if(cpuLight != null) {
                cpuLight.close();
            }
        }
    }
}
