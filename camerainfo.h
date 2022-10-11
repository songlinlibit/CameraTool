#ifndef CAMERAINFO_H
#define CAMERAINFO_H

#include<Include/VimbaCPP.h>
#include<QStringList>

class CameraInfo
{
private:
    AVT::VmbAPI::CameraPtr       m_Cam;
    QString         m_DisplayName;
    bool            m_IsOpen;
    QStringList     m_PermittedAccess;
    QStringList     m_PermittedAccessState;
public:
    CameraInfo()
        : m_IsOpen( false )
    {
    }
    explicit CameraInfo(AVT::VmbAPI::CameraPtr cam, const QString & name)
        : m_Cam( cam )
        , m_DisplayName( name )
        , m_IsOpen( false )
    {
    }
    const AVT::VmbAPI::CameraPtr &   Cam()                                       const   { return m_Cam; }
    AVT::VmbAPI::CameraPtr &         Cam()                                               { return m_Cam; }
    const QString&      DisplayName()                               const   { return m_DisplayName; }
    bool                IsOpen()                                    const   { return m_IsOpen; }
    void                SetOpen(bool s)                                     { m_IsOpen = s; }
    const QStringList&  PermittedAccess()                           const   { return m_PermittedAccess; }
    void                PermittedAccess( const QStringList &l)              { m_PermittedAccess = l; }
    const QStringList&  PermittedAccessState()                      const   { return m_PermittedAccessState; }
    void                PermittedAccessState(const QStringList &l)          { m_PermittedAccessState = l; }
    void SetPermittedAccessState(unsigned int pos, QString status)
    {
        m_PermittedAccessState[pos] = status;
    }
    void ResetPermittedAccessState()
    {
        for( int pos = 0; pos < m_PermittedAccessState.size(); ++ pos )
        {
            m_PermittedAccessState[pos] = "false";
        }
    }


    bool operator==( const AVT::VmbAPI::CameraPtr &other)                        const   { return SP_ACCESS(other) == SP_ACCESS( m_Cam); }
    bool operator<( const AVT::VmbAPI::CameraPtr &other)                         const   { return SP_ACCESS(other) < SP_ACCESS( m_Cam); }
    VmbInterfaceType InterfaceType() const
    {
        VmbInterfaceType interfaceType;
        VmbErrorType result = SP_ACCESS( m_Cam )->GetInterfaceType( interfaceType );
        if( result != VmbErrorSuccess )
        {
            throw std::runtime_error("could not read interface type from camera");
        }
        return interfaceType;
    }
    QString InterfaceTypeString() const
    {
        VmbInterfaceType interfaceType;
        VmbErrorType result = SP_ACCESS( m_Cam )->GetInterfaceType( interfaceType );
        if( result != VmbErrorSuccess )
        {
            throw std::runtime_error("could not read interface type from camera");
        }
        switch( interfaceType )
        {
        case VmbInterfaceEthernet:
            return "GigE";
        case VmbInterfaceFirewire:
            return "1394";
        case VmbInterfaceUsb:
            return "USB";
        case VmbInterfaceCL:
            return "CL";
        case VmbInterfaceCSI2:
            return "CSI2";
        }

    }
    typedef QVector<CameraInfo>     CameraInfoVector;
};

class FindByName
{
    const QString m_Name;
public:
    FindByName( const QString &s)
        : m_Name( s )
    {}
    bool operator()( const CameraInfo &i) const
    {
        return i.DisplayName() == m_Name;
    }
};
class CameraPtrCompare
{
    const AVT::VmbAPI::CameraPtr m_Camera;
public:
    CameraPtrCompare( const AVT::VmbAPI::CameraPtr& cam)
        : m_Camera( cam )
    {}
    bool operator() ( const AVT::VmbAPI::CameraPtr& other) const
    {
        return m_Camera.get() == other.get();
    }
};


#endif // CAMERAINFO_H
