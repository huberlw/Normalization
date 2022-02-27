import java.io.*;
import java.util.ArrayList;
import java.util.Scanner;

public class normalize
{
    private static double[] normal(ArrayList<String> array)
    {
        int size = array.size();

        double[] allNum = new double[size];

        double sum = 0;

        try
        {
            for(int i = 0; i < size; i++)
            {
                String temp = array.get(i);
                temp = temp.replaceAll("\\uFEFF", "");

                double n = Double.parseDouble(temp);
                allNum[i] = n;
                sum += n;
            }

        }
        catch(NumberFormatException nfe)
        {
            return new double[0];
        }

        // get mean
        double mean = sum / size;
        double sd = 0;

        double min = Double.MAX_VALUE;
        double max = Double.MIN_VALUE;

        // get Standard Deviation
        for(int i = 0; i < size; i++)
        {
            double temp = Math.pow((allNum[i] - mean), 2);
            sd += temp;
        }

        sd /= size;
        sd = Math.sqrt(sd);

        // subtract mean then divide by standard deviation
        for(int i = 0; i < size; i++)
        {
            allNum[i] = (allNum[i] - mean) / sd;

            if(allNum[i] > max) max = allNum[i];
            if(allNum[i] < min) min = allNum[i];
        }

        double div = max - min;

        // normalize data
        for(int i = 0; i < size; i++)
            allNum[i] = (allNum[i] - min) / div;

        return allNum;
    }

    public static void main(String[] args)
    {
        System.out.print("Enter csv file path: ");
        Scanner scan1 = new Scanner(System.in);

        String path = scan1.nextLine();
        String line;

        System.out.println("Is the first column for ID? (Y/N)");

        boolean done = false;
        boolean id = false;

        while(!done)
        {
            Scanner scan2 = new Scanner(System.in);

            String temp = scan2.nextLine();

            if(temp.equals("Y") || temp.equals("y"))
            {
                id = true;
                done = true;
            }
            else if(temp.equals("N") || temp.equals("n"))
                done = true;
            else
                System.out.println("Please enter a (Y/N).\nIs the first column for ID? (Y/N)");
        }

        System.out.println("Is the first row for labels? (Y/N)");
        done = false;

        boolean label = false;
        String[] labels = new String[0];

        while(!done)
        {
            Scanner scan3 = new Scanner(System.in);

            String temp = scan3.nextLine();

            if(temp.equals("Y") || temp.equals("y"))
            {
                label = true;
                done = true;
            }
            else if(temp.equals("N") || temp.equals("n"))
                done = true;
            else
                System.out.println("Please enter a (Y/N).\nIs the first row for labels? (Y/N)");
        }

        System.out.println();

        BufferedReader reader = null;

        try
        {
            reader = new BufferedReader(new FileReader(path));

            if(label && (line = reader.readLine()) != null)
                labels = line.split(",");

            ArrayList<String>[] cols = null;

            boolean first = true;
            int len = 0;

            while((line = reader.readLine()) != null)
            {
                String[] row = line.split(",");

                if(line.trim().isEmpty()) continue;

                if(first)
                {
                    len = row.length;

                    cols = new ArrayList[len];

                    for(int i = 0; i < len; i++)
                    {
                        cols[i] = new ArrayList<>();
                        cols[i].add(row[i]);
                    }

                    first = false;
                    continue;
                }

                for(int i = 0; i < len; i++)
                    cols[i].add(row[i]);
            }

            int size;
            if(cols == null)
            {
                System.out.println("File is empty.");
                return;
            }
            else
                size = cols[0].size();

            double[][] normData = new double[len][];
            String[][] stringData = new String[len][];

            for(int i = 0; i < len; i++)
            {
                if(!id)
                    normData[i] = normal(cols[i]);
                else
                {
                    stringData[i] = cols[i].toArray(new String[size]);
                    normData[i] = new double[0];
                    id = false;
                }

                if(normData[i].length == 0)
                    stringData[i] = cols[i].toArray(new String[size]);
            }

            File csv = new File("normalized.csv");
            PrintWriter out = new PrintWriter(csv);

            if(label)
            {
                for(int i = 0; i < labels.length; i++)
                {
                    if(i != labels.length - 1)
                        out.printf("%s, ", labels[i]);
                    else
                        out.printf("%s\n", labels[i]);
                }
            }

            for(int i = 0; i < size; i++)
            {
                for(int j = 0; j < len; j++)
                {
                    if(normData[j].length == 0)
                    {
                        if(j != len - 1)
                            out.printf("%s, ", stringData[j][i]);
                        else
                            out.printf("%s\n", stringData[j][i]);
                    }
                    else
                    {
                        if(j != len - 1)
                            out.printf("%.3f, ", normData[j][i]);
                        else
                            out.printf("%.3f\n", normData[j][i]);
                    }
                }
            }

            out.close();

            System.out.println("Normalization complete.");
        }
        catch(IOException e)
        {
            e.printStackTrace();
        }
        finally
        {
            try
            {
                reader.close();
            }
            catch(IOException e)
            {
                e.printStackTrace();
            }
        }

    }
}