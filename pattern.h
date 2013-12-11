#ifndef LZ_PATTERN_H
#define LZ_PATTERN_H

#include <QJsonObject>
#include <QStringList>

namespace Lz {

/* Forward declaration.  */
class RenderedPattern;

/**
 * @brief Abstract parent for patterns in different formats (image, docx, ...)
 */
class Pattern
{
public:
    /**
     * @brief   Construct a pattern using given config
     * @param   config              Pattern config as a json object. "fields" field value should be a json object: {..., fields : {$field1_name : ..., $field2_name: ..., ...}, ...}
     */
    Pattern(const QJsonObject& config);
    virtual ~Pattern();

    /**
     * @brief   Factory method to construct a @a Pattern using given config.
     * @param   config              Pattern config as a json object. "type" field contains a pattern type. Currently supports only "image" type.
     * @return                      Pattern object if constructed successully, 0 otherwise.
     */
    static Pattern* construct(const QJsonObject& config);

    virtual RenderedPattern* render(const QJsonObject& info) = 0;

    /**
     * @brief   Return the list of fields the pattern contains.
     * @return                      Field list.
     */
    QStringList fields();

private:
    QStringList                     m_fields;
};

} // namespace Lz

#endif // LZ_PATTERN_H
