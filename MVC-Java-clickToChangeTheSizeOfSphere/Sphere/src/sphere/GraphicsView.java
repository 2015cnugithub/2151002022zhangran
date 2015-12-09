/*
 * GraphicsView.java
 *
 *
 * To change this template, choose Tools | Template Manager
 * and open the template in the editor.
 */

/**
 *
 * @author cnu
 */
package sphere;

import java.util.Observer;
import java.util.Observable;

import javax.swing.*;

import java.awt.*;
import java.awt.event.MouseMotionAdapter;
//该类为图形视图，用图形显示球
public class GraphicsView extends javax.swing.JPanel implements Observer {
    
    private double radius=0;
    
    /** Creates a new instance of GraphicsView */
    public GraphicsView() {
        this.setSize(200, 200);
        this.setBackground(new Color(255,255,255));
    }
    
    public void update(Observable o, Object arg) {
        Sphere s=(Sphere)o;
        radius=s.getRadius();
        //调用paintComponent()函数，重新画
        repaint();
    }
   
    protected void paintComponent(Graphics g) {
        super.paintComponent(g);
        int r=(int)radius;
        int r1=(int)radius*2;
        int r2=(int)radius/2;
        //用一个圆和两个椭圆模拟一个球
        g.drawOval(0, 0, r1, r1);
        g.drawOval(r2, 0, r, r1);
        g.drawOval(0, r2, r1, r);
    }


}