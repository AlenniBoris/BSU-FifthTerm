import java.awt.*;
import java.util.ArrayList;
import java.util.concurrent.atomic.AtomicReferenceArray;

public class Methods {
    static ArrayList<Pixel> brezenheim(int x0, int y0, int x1, int y1){
        ArrayList<Pixel> points = new ArrayList<>();

        if (x1-x0 < 0){
            int tempx = x0;
            int tempy = y0;
            x0 = x1;
            y0 = y1;
            x1 = tempx;
            y1 = tempy;
        }

        int dx = x1-x0;
        int dy = Math.abs(y1-y0);

        int error = dx/2;
        int ystep = (y0 < y1) ? 1 : -1;
        int y = y0;

        for (int x = x0; x <= x1; x++) {
            points.add(new Pixel(x,y));
            error -= dy;
            if (error < 0){
                y += ystep;
                error += dx;
            }
        }
        return points;
    }

    static ArrayList<Pixel> stepByStep(int x0, int y0, int x1, int y1){
        ArrayList<Pixel> points = new ArrayList<>();

        if (x1-x0 < 0){
            int tempx = x0;
            int tempy = y0;
            x0 = x1;
            y0 = y1;
            x1 = tempx;
            y1 = tempy;
        }

        int dx = x1-x0;
        int dy = y1-y0;
        double k = (double) dy /dx;
        double b = y0 - k*x0;
        int y = y0;

        for (int x = x0; x <= x1; x++) {
            y = (int) (k*x+b);
            points.add(new Pixel(x, y));
        }

        return points;
    }
}
