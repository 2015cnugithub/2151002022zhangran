package sphere;

import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;

public class GraphicsController implements MouseListener{
    //该控制器所控制的Sphere对象
    private Sphere sphere;
    
    /** Creates a new instance of TextController */
    public GraphicsController(Sphere sphere) {
        this.sphere=sphere;
    }

	@Override
	public void mouseClicked(MouseEvent e) {
		// TODO Auto-generated method stub
		double x = e.getX();
		double y = e.getY();
		double p = Math.sqrt(x*x + y*y);
		double r = sphere.getRadius();
		if(x >r&&y>r){
			r = p/(1+Math.sqrt(2));
		}
		else if(x<r&&y<r){
			r=p/(Math.sqrt(2)-1);
		}
		else {
			r = Math.sqrt((x-r)*(x-r) + (y-r)*(y-r));
		}
		r = Math.sqrt((x-r)*(x-r) + (y-r)*(y-r));
		sphere.setRadius(r);
		
	}

	@Override
	public void mouseEntered(MouseEvent e) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void mouseExited(MouseEvent e) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void mousePressed(MouseEvent e) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void mouseReleased(MouseEvent e) {
		// TODO Auto-generated method stub
		
	}
    

}

