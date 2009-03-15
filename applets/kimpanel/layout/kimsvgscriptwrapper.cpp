#include "kimsvgscriptwrapper.h"
#include <KDebug>
#include <QtScript>

namespace KIM
{

    SvgScriptWrapper::SvgScriptWrapper(KSvgRenderer *render,QScriptEngine *engine,QObject *parent)
        :QObject(parent),
         m_render(render),
         m_engine(engine)
    {

    }
    
    QScriptValue SvgScriptWrapper::Element(const QString &elemId)
    {
        QString elem = elemId;
        if (elem.isEmpty()) {
            elem = "root";
        }
        if (m_items.contains(elem)) {
            QScriptValue val = m_engine->newQObject(m_items[elem]);
            return val;
        } else {
            QSizeF size = m_render->boundsOnElement(elem).size();
            SvgScriptItem *item = new SvgScriptItem(elem,size);
            m_items[elem] = item;
            QScriptValue val = m_engine->newQObject(item);
            return val;
        }
    }
} // namespace KIM

// vim: sw=4 sts=4 et tw=100
