import javax.swing.*;
import java.awt.*;
import java.awt.geom.*;
import java.util.ArrayList;

public class GraphPlotter extends JFrame {

    private ArrayList<Pixel> shadedCells;
    private int maxCoordinate; // Максимальная координата от центра

    public GraphPlotter(ArrayList<Pixel> shadedCells, String text, int maxCoordinate) {
        this.shadedCells = shadedCells;
        this.maxCoordinate = maxCoordinate;

        setTitle(text);
        setLocationRelativeTo(null);

        // Рассчитываем размер окна исходя из максимальной координаты и размеров клетки
        int cellSize = 20; // Размер клетки
        int windowSize = (maxCoordinate + 3) * cellSize * 2;
        setSize(windowSize, windowSize);

        JPanel graphPanel = new JPanel() {
            @Override
            protected void paintComponent(Graphics g) {
                super.paintComponent(g);
                Graphics2D g2d = (Graphics2D) g;

                int centerX = getWidth() / 2;
                int centerY = getHeight() / 2;

                // Рисование осей
                g2d.setColor(Color.BLACK);
                g2d.draw(new Line2D.Double(centerX, 0, centerX, getHeight()));
                g2d.draw(new Line2D.Double(0, centerY, getWidth(), centerY));

                // Рисование сетки
                g2d.setColor(Color.LIGHT_GRAY);
                drawGrid(g2d, centerX, centerY, cellSize);

                // Рисование подписей осей
                drawAxisLabels(g2d, centerX, centerY, cellSize);

                // Закрашивание клеток
                g2d.setColor(Color.BLUE);
                shadeCells(g2d, centerX, centerY, cellSize);
            }
        };

        add(graphPanel);
    }

    private void drawGrid(Graphics2D g2d, int centerX, int centerY, int cellSize) {
        int divisions = (maxCoordinate + 1) * 2; // Количество делений в обеих осях

        for (int i = -divisions / 2; i <= divisions / 2; i++) {
            int x = centerX + i * cellSize;
            int y = centerY + i * cellSize;

            g2d.draw(new Line2D.Double(x, 0, x, getHeight()));
            g2d.draw(new Line2D.Double(0, y, getWidth(), y));
        }
    }

    private void drawAxisLabels(Graphics2D g2d, int centerX, int centerY, int cellSize) {
        g2d.setColor(Color.BLACK);
        g2d.drawString("X", getWidth() - 20, centerY - 10);
        g2d.drawString("Y", centerX + 10, 20);

        int labelOffset = 5;
        int divisions = (maxCoordinate + 1) * 2; // Количество делений в обеих осях

        for (int i = 1; i <= divisions / 2; i++) {
            int x = centerX + i * cellSize;
            int y = centerY - i * cellSize;

            g2d.drawString(String.valueOf(i), x - labelOffset, centerY + labelOffset);
            g2d.drawString(String.valueOf(-i), 2 * centerX - x - labelOffset, centerY + labelOffset);

            g2d.drawString(String.valueOf(i), centerX -  labelOffset, y + labelOffset);
            g2d.drawString(String.valueOf(-i), centerX - labelOffset, 2*centerY - y - labelOffset);
        }
    }

    private void shadeCells(Graphics2D g2d, int centerX, int centerY, int cellSize) {
        for (Pixel cell : shadedCells) {
            int x = cell.getX() * cellSize + centerX;
            int y = -cell.getY() * cellSize + centerY - cellSize; // Инвертирование y для соответствия координатной системе

            g2d.fill(new Rectangle2D.Double(x, y, cellSize, cellSize));
        }
    }
}
