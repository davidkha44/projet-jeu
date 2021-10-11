#include "Handler.hpp"
#include "Manageable.hpp"

class SelectionHandler : public Handler
{
    ATTRIBUTE(std::vector<Manageable>,Selection);

    public :
        SelectionHandler();
        void Add(Manageable);
        void Remove(Manageable);
        void OnTurnBegin() override;
};