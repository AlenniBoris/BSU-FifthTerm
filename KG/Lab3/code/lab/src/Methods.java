import java.awt.*;
import java.util.ArrayList;
import java.util.concurrent.atomic.AtomicReferenceArray;

public class Methods {
    static ArrayList<Pixel> brezenheim(int x0, int y0, int x1, int y1){
        ArrayList<Pixel> points = new ArrayList<>();

        int dx = Math.abs(x1 - x0);
        int dy = Math.abs(y1 - y0);
        int sx = (x0 < x1) ? 1 : -1;
        int sy = (y0 < y1) ? 1 : -1;

        int error = dx - dy;

        while (true) {
            // Draw the current point
            points.add(new Pixel(x0,y0));

            if (x0 == x1 && y0 == y1) {
                break;
            }

            int error2 = 2 * error;

            if (error2 > -dy) {
                error -= dy;
                x0 += sx;
            }

            if (error2 < dx) {
                error += dx;
                y0 += sy;
            }
        }

        return points;
    }

    static ArrayList<Pixel> stepByStep(int x0, int y0, int x1, int y1){
        ArrayList<Pixel> points = new ArrayList<>();

        int dx = x1 - x0;
        int dy = y1 - y0;

        int steps = Math.max(Math.abs(dx), Math.abs(dy));

        double xIncrement = (double) dx / steps;
        double yIncrement = (double) dy / steps;

        double x = x0;
        double y = y0;

        for (int i = 0; i <= steps; i++) {
            points.add(new Pixel((int) x, (int) y));
            x += xIncrement;
            y += yIncrement;
        }

        return points;
    }
}
