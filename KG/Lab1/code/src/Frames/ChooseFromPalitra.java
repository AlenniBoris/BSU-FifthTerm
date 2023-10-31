package Frames;

import Frames.MainFrame;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class ChooseFromPalitra extends JPanel {
    private JButton choose;
    private MainFrame frame;

    public ChooseFromPalitra(MainFrame mainFrame) {
        frame = mainFrame;
        choose = new JButton("Palitra");

        setLayout(new GridLayout(2,0));
        add(choose);
        choose.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                Color color = JColorChooser.showDialog(null,"Select color", Color.BLACK);
                if (color != null){
                    frame.getColorPanel().setBackground(color);
                    frame.getRGB().changeTextFields(color.getRed(), color.getGreen(), color.getBlue());
                    frame.getRGB().changeCMYK(color.getRed(), color.getGreen(), color.getBlue());
                    frame.getRGB().changeHSL(color.getRed(), color.getGreen(), color.getBlue());
                }
            }
        });
    }
}
