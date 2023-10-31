import org.opencv.core.Mat;
import org.opencv.core.MatOfByte;
import org.opencv.imgcodecs.Imgcodecs;

import javax.imageio.ImageIO;
import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.image.BufferedImage;
import java.io.ByteArrayInputStream;
import java.io.IOException;
import java.io.InputStream;


public class ControlPanel extends JPanel {
    private MainFrame mainFrame;
    private JPanel first;
    private JPanel second;
    private JPanel third;
    private JPanel fourth;

    private JButton load;
    private JButton save;
    private JButton reset;
    private JButton logarithm;
    private JButton negative;
    private JButton localThreshBtn;
    private JButton linearContrastBtn;
    private JButton addBtn;
    private JButton multiplyBtn;
    private JButton powerBtn;

    private JTextField localThreshFirst;
    private JTextField localThreshSecond;
    private JTextField localThreshThird;
    private JTextField linearContrastFirst;
    private JTextField linearContrastSecond;
    private JTextField addFirst;
    private JTextField multiplyFirst;
    private JTextField powerFirst;

    private Mat image;
    private Mat workingImage;
    private Mat niblackImage;
    private Mat pic;
    private Mat picB;
    private Mat picN;
    private BufferedImage bufImage;
    private BufferedImage workingBufImage;
    private BufferedImage nibkackBufImage;

    private String loadedPic;

    public ControlPanel(MainFrame mainFrame) {
        this.mainFrame = mainFrame;

        setLayout(new GridLayout(1, 4));

        first = new JPanel(new GridLayout(3, 1));
        load = new JButton("Load");

        load.addActionListener(e -> {
            JFileChooser fileChooser = new JFileChooser("./photos/default");
            int r = fileChooser.showOpenDialog(null);
            if (r == JFileChooser.APPROVE_OPTION) {
                image = Imgcodecs.imread(fileChooser.getSelectedFile().getAbsolutePath());
                loadedPic = fileChooser.getSelectedFile().getAbsolutePath().replaceAll("^.+([^\\\\\\\\]+)\\\\", "").replaceAll(".jpg","");

                pic = image;

                try {
                    bufImage = toBufImage(image);
                } catch (IOException ex) {
                    throw new RuntimeException(ex);
                }

                mainFrame.getImagePanel().setPicOrigin(bufImage);
                mainFrame.getImagePanel().setPicProcessed(bufImage);

                mainFrame.getImagePanel().getSizeField().setText(String.valueOf(image.size()));
                mainFrame.getImagePanel().getOperation().setText("no_operation");
            }
        });

        save = new JButton("Save");
        save.addActionListener(e -> {
            if (image!=null){
                if (mainFrame.getImagePanel().getOperation().getText().equals("Thresholding")){
                    String bernsenPath = "./photos/operations/Thresholding/"+loadedPic+"_bernsen"+".jpg";
                    String niblackPath = "./photos/operations/Thresholding/"+loadedPic+"_niblack"+".jpg";
                    Imgcodecs.imwrite(bernsenPath, picB);
                    Imgcodecs.imwrite(niblackPath, picN);
                    JOptionPane.showMessageDialog(null, "Сохранено в папку: photos/operations/"+mainFrame.getImagePanel().getOperation().getText());
                }
                else{
                    String path = "./photos/operations/"+mainFrame.getImagePanel().getOperation().getText()+"/"+loadedPic+".jpg";
                    Imgcodecs.imwrite(path, pic);
                    JOptionPane.showMessageDialog(null, "Сохранено в папку: photos/operations/"+mainFrame.getImagePanel().getOperation().getText());
                }
            }
        });

        reset = new JButton("Reset");
        reset.addActionListener(e -> {
            mainFrame.getImagePanel().setPicProcessed(bufImage);
            pic = image;
            mainFrame.getImagePanel().getLabelPr1().setIcon(new ImageIcon());
            mainFrame.getImagePanel().getOperation().setText("no_operation");
        });

        first.add(load);
        first.add(save);
        first.add(reset);

        second = new JPanel(new GridLayout(5, 1));
        JTextField thresholding = new JTextField("Local thresholding");
        thresholding.setEditable(false);
        second.add(thresholding);
        localThreshFirst = new JTextField("Size");
        localThreshSecond = new JTextField("Bernsen");
        localThreshThird = new JTextField("Niblack");
        second.add(localThreshFirst);
        second.add(localThreshSecond);
        second.add(localThreshThird);
        localThreshBtn = new JButton("Thresholding");
        localThreshBtn.addActionListener(e -> {
            try {
                if (image != null) {
                    int size = Integer.parseInt(localThreshFirst.getText());
                    int C = Integer.parseInt(localThreshSecond.getText());
                    double K = Double.parseDouble(localThreshThird.getText());

                    workingImage = image;
                    niblackImage = image;

                    picB = ElementTransformations.Bernsen(workingImage, size, C);
                    picN = ElementTransformations.Niblack(niblackImage, size, K);

                    try {
                        workingBufImage = toBufImage(picB);
                        nibkackBufImage = toBufImage(picN);
                    } catch (IOException ex) {
                        throw new RuntimeException(ex);
                    }

                    mainFrame.getImagePanel().setPicProcessed(workingBufImage);
                    mainFrame.getImagePanel().setPicNiblack(nibkackBufImage);
                    mainFrame.getImagePanel().setPicOrigin(bufImage);
                    mainFrame.getImagePanel().getOperation().setText(localThreshBtn.getText());
                }
            } catch (NumberFormatException exception) {
                JOptionPane.showMessageDialog(null, "Вводите нечентые числа > 0");
            }
        });
        second.add(localThreshBtn);

        third = new JPanel(new GridLayout(4, 1));
        JTextField contrasting = new JTextField("Linear contrast");
        contrasting.setEditable(false);
        third.add(contrasting);
        linearContrastFirst = new JTextField("min");
        linearContrastSecond = new JTextField("max");
        third.add(linearContrastFirst);
        third.add(linearContrastSecond);
        linearContrastBtn = new JButton("Contrast");
        linearContrastBtn.addActionListener(e -> {
            try {
                if (image != null) {
                    int min = Integer.parseInt(linearContrastFirst.getText());
                    int max = Integer.parseInt(linearContrastSecond.getText());

                    if (!(min < 0) && !(max > 255)) {
                        pic = ElementTransformations.linearContrast(image, min, max);
                        try {
                            workingBufImage = toBufImage(pic);
                        } catch (IOException ex) {
                            throw new RuntimeException(ex);
                        }
                        mainFrame.getImagePanel().setPicProcessed(workingBufImage);
                        mainFrame.getImagePanel().getOperation().setText(linearContrastBtn.getText());

                    } else {
                        JOptionPane.showMessageDialog(null, "Вводите числа >= 0 и <= 255");
                    }
                }
            } catch (NumberFormatException exception) {
                JOptionPane.showMessageDialog(null, "Вводите числа");
            }
        });
        third.add(linearContrastBtn);

        fourth = new JPanel();
        fourth.setLayout(new GridLayout(4, 1));

        JPanel addPnl = new JPanel(new BorderLayout());
        JTextField adding = new JTextField("Add");
        adding.setEditable(false);
        addPnl.add(adding, BorderLayout.NORTH);
        addBtn = new JButton("Add");
        addPnl.add(addBtn, BorderLayout.WEST);
        addFirst = new JTextField("number");
        addPnl.add(addFirst);
        addBtn.addActionListener(e -> {
            try {
                if (image != null) {
                    int value = Integer.parseInt(addFirst.getText());

                    pic = ElementTransformations.addValue(image, value);
                    try {
                        workingBufImage = toBufImage(pic);
                    } catch (IOException ex) {
                        throw new RuntimeException(ex);
                    }
                    mainFrame.getImagePanel().setPicProcessed(workingBufImage);
                    mainFrame.getImagePanel().getOperation().setText(addBtn.getText());
                }
            } catch (NumberFormatException exception) {
                JOptionPane.showMessageDialog(null, "Вводите числа");
            }
        });
        fourth.add(addPnl);

        JPanel multiplyPnl = new JPanel(new BorderLayout());
        JTextField multiplying = new JTextField("Multiply");
        multiplying.setEditable(false);
        multiplyPnl.add(multiplying, BorderLayout.NORTH);
        multiplyBtn = new JButton("Multiply");
        multiplyPnl.add(multiplyBtn, BorderLayout.WEST);
        multiplyFirst = new JTextField("number");
        multiplyPnl.add(multiplyFirst);
        multiplyBtn.addActionListener(e -> {
            try {
                if (image != null) {
                    double value = Double.parseDouble(multiplyFirst.getText());

                    pic = ElementTransformations.multiplyValue(image, value);
                    try {
                        workingBufImage = toBufImage(pic);
                    } catch (IOException ex) {
                        throw new RuntimeException(ex);
                    }
                    mainFrame.getImagePanel().setPicProcessed(workingBufImage);
                    mainFrame.getImagePanel().getOperation().setText(multiplyBtn.getText());
                }
            } catch (NumberFormatException exception) {
                JOptionPane.showMessageDialog(null, "Вводите числа");
            }
        });
        fourth.add(multiplyPnl);

        JPanel powerPnl = new JPanel(new BorderLayout());
        JTextField powering = new JTextField("Power");
        powering.setEditable(false);
        powerPnl.add(powering, BorderLayout.NORTH);
        powerBtn = new JButton("Power");
        powerPnl.add(powerBtn, BorderLayout.WEST);
        powerFirst = new JTextField("number");
        powerPnl.add(powerFirst);
        powerBtn.addActionListener(e -> {
            try {
                if (image != null) {
                    double value = Double.parseDouble(powerFirst.getText());

                    pic = ElementTransformations.powerValue(image, value);
                    try {
                        workingBufImage = toBufImage(pic);
                    } catch (IOException ex) {
                        throw new RuntimeException(ex);
                    }
                    mainFrame.getImagePanel().setPicProcessed(workingBufImage);
                    mainFrame.getImagePanel().getOperation().setText(powerBtn.getText());
                }
            } catch (NumberFormatException exception) {
                JOptionPane.showMessageDialog(null, "Вводите числа");
            }
        });
        fourth.add(powerPnl);

        JPanel otherPnl = new JPanel(new GridLayout(1, 2, 3, 0));
        negative = new JButton("Negative");
        negative.addActionListener(e -> {
            if (image != null) {
                pic = ElementTransformations.toNegative(image);
                try {
                    workingBufImage = toBufImage(pic);
                } catch (IOException ex) {
                    throw new RuntimeException(ex);
                }
                mainFrame.getImagePanel().setPicProcessed(workingBufImage);
                mainFrame.getImagePanel().getOperation().setText(negative.getText());
            }
        });
        logarithm = new JButton("Logarithm");
        logarithm.addActionListener(e -> {
            if (image != null) {
                pic = ElementTransformations.logarithm(image);
                try {
                    workingBufImage = toBufImage(pic);
                } catch (IOException ex) {
                    throw new RuntimeException(ex);
                }
                mainFrame.getImagePanel().setPicProcessed(workingBufImage);
                mainFrame.getImagePanel().getOperation().setText(logarithm.getText());
            }
        });
        otherPnl.add(negative);
        otherPnl.add(logarithm);
        fourth.add(otherPnl);

        add(first);
        add(second);
        add(third);
        add(fourth);
    }

    private BufferedImage toBufImage(Mat image) throws IOException {
        MatOfByte matOfByte = new MatOfByte();
        Imgcodecs.imencode(".jpg", image, matOfByte);
        byte[] byteArray = matOfByte.toArray();
        InputStream in = new ByteArrayInputStream(byteArray);
        return ImageIO.read(in);
    }
}
