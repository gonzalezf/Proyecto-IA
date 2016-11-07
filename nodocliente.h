using namespace std;


class NodoCliente{

	private:
		int idCliente;
		double posicionx;
		double posiciony;
		int demanda;

	public:
		NodoCliente();
		NodoCliente(int id, double x, double y, int d);
		int getId();
		void setId(int id);
		double getCoordenadaX();
		double getCoordenadaY();
		void setPosicion(double x, double y);
		int getDemanda();
		void setDemanda(int d);


};

