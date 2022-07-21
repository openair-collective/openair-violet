import React from 'react'

//configuration file that has the values stored for users
import config from '../utils/userconfig'

class Dashboard extends React.Component {
    render() {
        //suppose user is received from props
        const { user } = this.props
        return (
            <>
                {/** different dashboards for different organizations
                 * depending upon the parameters their panels value changes
                 */}
                {(config.roles.user1_org1 === user.role.id) &&
                    <iframe
                        src={`https://${config.sampleDash.organization1.username}:${config.sampleDash.organization1.password}@authproxy.sampleDomain/z/aaaaaaaaa/organization_1?orgId=1&from=now-90d&to=now&var-org_user=${type}&var-state=${state}&var-top=5&kiosk=tv`} />
                }
                {(config.roles.user2_org3 === user.role.id) &&
                    <iframe
                        src={`https://${config.sampleDash.organization3.username}:${config.sampleDash.organization3.password}@authproxy.sampleDomain/z/ccccccccc/organization_3?orgId=3&from=now-90d&to=now&var-org_user=${user.username}&var-city=${city}&kiosk=tv`} />
                }
                {(config.roles.user3_org2 === user.role.id) &&
                    <iframe
                        src={`https://${config.sampleDash.organization2.username}:${config.sampleDash.organization2.password}@authproxy.sampleDomain/z/bbbbbbbbb/organization_2?orgId=2&from=now-90d&to=now&var-org_user=${user.username}&kiosk=tv`} />
                }
            </>
        )
    }
}
export default Dashboard