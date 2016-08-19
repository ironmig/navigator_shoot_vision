#ifndef SMART_HPP
#define SMART_HPP
class ImageSearcher {
  private:

    ros::NodeHandle n;
    ros::Subscriber sub;
    ros::ServiceServer service;

  public:
  	   static navigator_shoot_vision::Symbols syms;
    ImageSearcher() {
    	syms = navigator_shoot_vision::Symbols();
        sub = n.subscribe("found_shapes", 1000, chatterCallback);
//        service = n.advertiseService("GetShape", test);
    }
   static void chatterCallback(const navigator_shoot_vision::Symbols &symbols) { 
   syms = symbols;
std::cout<<symbols.list.size()<<std::endl;
   }

//  static  bool test(navigator_shoot_vision::GetShape::Request &req, navigator_shoot_vision::GetShape::Response &res) {
////        for(int i = 0; i < syms.size(); i++) {
//        	for(int j =0; j < syms.list.size(); j++) {
//        		if(req.Shape == syms.list[j].Shape && req.Color == syms.list[j].Color) {
//        			res.CenterX = syms.list[j].CenterX;
//        			res.CenterY = syms.list[j].CenterY;
//        		}
//   			 }
//   			 }
//   			 }
};

#endif
