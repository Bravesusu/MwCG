
#include "mwglelement.h"
#include "LineFactory.h"
namespace mw
{
	class Line;
	class BresLine;

	
	class Polygon :
		public GlElement
	{
		//DECLARE_SERIAL(Polygon);
	private:
		list<shared_ptr<Vector2>> vertex_;
		shared_ptr<Line> line_;
		shared_ptr<LineFactory> line_factory_;
	public:
		void set_line(LineFactory* factory);
	public:
		int count() const { return vertex_.size(); }
		void NewVertex(const Vector2& pos);
		void UpdateLastVertext(const Vector2& pos);
	public:
		Polygon(void);
		Polygon(LineFactory* factory);
		Polygon(shared_ptr<LineFactory> factory);
		~Polygon(void);

		virtual void Serialize( CArchive& ar );

		virtual void DoDraw();

		//virtual bool HitTest();

		virtual Rect bound() const;

		virtual void Draw();

	};
	
}
