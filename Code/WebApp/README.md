# This is the OpenAir Violet Progressive WebApp (PWA)

## How to setup the dev environment

> **Note**: you must have NodeJS and npm installed on your computer

1. `cd OpenAir-Violet`
2. Run the `npm install` command
3. Run the `npm run dev` command (this will start a dev server)
4. Open the browser and navigate to the address listed in your console
5. Enjoy!

There is Hot Module Reloading, so you can edit the code and see the changes immediately.

## How to setup the production environment

> **Note**: you can only deploy the PWA to the live link if you are logged in with my account currently - please do not try to deploy yet.
> Eventually we will migrate to a dedicated account and server for this, but for now, you can upload to the github, and i will deploy to the live link.

 1. `cd OpenAir-Violet`
 2. Run the `npm run build` command (this will create a production build)
 3. Next run `firebase deploy --only hosting:openair-violet`
 4. Open the browser and navigate to the address listed in your console
 5. Enjoy!
