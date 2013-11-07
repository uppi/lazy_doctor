#ifndef LZ_CORE_H
#define LZ_CORE_H

namespace Lz {

class PatternStorage;

class Core
{


public:
    Core();

private:
    PatternStorage* m_patternStorage;    
};

} // namespace Lz

#endif // LZ_CORE_H
