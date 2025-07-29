import { svg } from "lit";

export const items = [
  {
    title: "Dashboard",
    href: "/",
    disabled: false,
    svg: svg`
          <svg xmlns="http://www.w3.org/2000/svg" height="48px" viewBox="0 -960 960 960" width="48px" fill="#5f6368">
            <path d="M240-200h120v-240h240v240h120v-360L480-740 240-560v360Zm-80 80v-480l320-240 320 240v480H520v-240h-80v240H160Zm320-350Z"/>
          </svg>
          `,
  },
  {
    title: "Image Gallery",
    href:
      import.meta.env.VITE_RZG2LC !== "true"
        ? "/webgl-gallery"
        : "/image-gallery",
    disabled: false,
    svg: svg`
          <svg xmlns="http://www.w3.org/2000/svg" height="48px" viewBox="0 -960 960 960" width="48px" fill="#5f6368">
							<path d="M120-200q-33 0-56.5-23.5T40-280v-400q0-33 23.5-56.5T120-760h400q33 0 56.5 23.5T600-680v400q0 33-23.5 56.5T520-200H120Zm600-320q-17 0-28.5-11.5T680-560v-160q0-17 11.5-28.5T720-760h160q17 0 28.5 11.5T920-720v160q0 17-11.5 28.5T880-520H720Zm40-80h80v-80h-80v80ZM120-280h400v-400H120v400Zm40-80h320L375-500l-75 100-55-73-85 113Zm560 160q-17 0-28.5-11.5T680-240v-160q0-17 11.5-28.5T720-440h160q17 0 28.5 11.5T920-400v160q0 17-11.5 28.5T880-200H720Zm40-80h80v-80h-80v80Zm-640 0v-400 400Zm640-320v-80 80Zm0 320v-80 80Z"/>
          </svg>
          `,
  },
  {
    title: "Home Automation",
    href: "/home-automation",
    disabled: false,
    svg: svg`
          <svg xmlns="http://www.w3.org/2000/svg" height="48px" viewBox="0 -960 960 960" width="48px" fill="#5f6368">
							<path d="M221-240q42 0 71-29t29-71q0-24-11-47t-33-37l-36-24v-252q0-9-5.5-14.5T221-720q-9 0-14.5 5.5T201-700v252l-36 24q-22 15-33 37t-11 47q0 42 29 71t71 29Zm0 80q-75 0-127.5-52T41-340q0-48 22-86t58-62v-212q0-42 29-71t71-29q42 0 71 29t29 71v212q36 24 58 62t22 86q0 75-52.5 127.5T221-160Zm327-200q-48-33-78-85t-30-115q0-100 70-170t170-70q100 0 170 70t70 170q0 63-30 115t-78 85H548Zm28-80h212q27-24 39.5-54t12.5-66q0-66-47-113t-113-47q-66 0-113 47t-47 113q0 36 14.5 66t41.5 54Zm104 280q-24 0-42-18t-18-42h120q0 24-18 42t-42 18Zm-120-80v-80h240v80H560ZM221-340Zm459-240Z"/>
          </svg>
          `,
  },
  {
    title: "Weather History",
    href: "/chart",
    disabled: false,
    svg: svg`
          <svg xmlns="http://www.w3.org/2000/svg" height="48px" viewBox="0 -960 960 960" width="48px" fill="#5f6368">
							<path d="M120-120v-80l80-80v160h-80Zm160 0v-240l80-80v320h-80Zm160 0v-320l80 81v239h-80Zm160 0v-239l80-80v319h-80Zm160 0v-400l80-80v480h-80ZM120-327v-113l280-280 160 160 280-280v113L560-447 400-607 120-327Z"/>
          </svg>
          `,
  },
  {
    title: "Live Camera",
    href: "/camera",
    disabled: false,
    svg: svg`
          <svg xmlns="svg" height="48px" viewBox="0 -960 960 960" width="48px" fill="#5f6368">
							<path d="M160-160q-33 0-56.5-23.5T80-240v-480q0-33 23.5-56.5T160-800h480q33 0 56.5 23.5T720-720v180l160-160v440L720-420v180q0 33-23.5 56.5T640-160H160Zm0-80h480v-480H160v480Zm0 0v-480 480Z"/>
          </svg>
          `,
  },
];

export default items;
