import { LitElement, css, html } from "lit";

export class DateWidget extends LitElement {
  constructor() {
    super();
    this._todayToString();
  }

  /**
   * Format the date
   * @param {Date} date Current year
   * @param {string} format Year of Birth
   * @returns {string} the formated date
   */
  _formatDate(date, format) {
    const dayNames = ["Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"];
    const montNames = [
      "Jan",
      "Feb",
      "Mar",
      "Apr",
      "May",
      "Jun",
      "Jul",
      "Aug",
      "Sep",
      "Oct",
      "Nov",
      "Dec",
    ];
    const map = {
      ww: dayNames[date.getDay()],
      mm: montNames[date.getMonth()],
      dd: date.getDate(),
      yy: date.getFullYear().toString().slice(-2),
      yyyy: date.getFullYear(),
    };

    return format.replace(/ww|mm|dd|yy|yyyy/gi, (matched) => map[matched]);
  }

  /**
   * Convert Date to formatted string
   */
  _todayToString() {
    const timeElapsed = Date.now();
    const today = new Date(timeElapsed);

    this.dateString = this._formatDate(today, "ww, dd mm yy");
  }

  render() {
    return html`
      <div class="container">
        <div class="icon">
          <svg
            width="18"
            height="18"
            viewBox="0 0 24 24"
            fill="none"
            xmlns="http://www.w3.org/2000/svg"
          >
            <g id="SVGRepo_iconCarrier">
              <path
                d="M7 4V2.5"
                stroke-width="1.5"
                stroke-linecap="round"
              ></path>
              <path
                d="M17 4V2.5"
                stroke-width="1.5"
                stroke-linecap="round"
              ></path>
              <path
                d="M9 14.5L10.5 13V17"
                stroke-width="1.5"
                stroke-linecap="round"
                stroke-linejoin="round"
              ></path>
              <path
                d="M13 16V14C13 13.4477 13.4477 13 14 13C14.5523 13 15 13.4477 15 14V16C15 16.5523 14.5523 17 14 17C13.4477 17 13 16.5523 13 16Z"
                stroke-width="1.5"
                stroke-linecap="round"
              ></path>
              <path
                d="M21.5 9H16.625H10.75M2 9H5.875"
                stroke-width="1.5"
                stroke-linecap="round"
              ></path>
              <path
                d="M14 22H10C6.22876 22 4.34315 22 3.17157 20.8284C2 19.6569 2 17.7712 2 14V12C2 8.22876 2 6.34315 3.17157 5.17157C4.34315 4 6.22876 4 10 4H14C17.7712 4 19.6569 4 20.8284 5.17157C22 6.34315 22 8.22876 22 12V14C22 17.7712 22 19.6569 20.8284 20.8284C20.1752 21.4816 19.3001 21.7706 18 21.8985"
                stroke-width="1.5"
                stroke-linecap="round"
              ></path>
            </g>
          </svg>
        </div>
        <div class="date-string">${this.dateString}</div>
      </div>
    `;
  }

  static styles = css`
    :host {
      display: block;
      width: 100%;
    }
    svg {
      overflow: visible;
      display: block;
      stroke: var(--date-widget-icon-color, #ddd);
      width: 24px;
      height: 24px;
    }
    .container {
      display: flex;
      gap: 0.5em;
      justify-content: space-between;
      align-items: center;
      padding: 0.5em 0.75rem;
      background-color: var(--date-widget-icon-color, #333);
      border-radius: 10px;
      max-width: 240px;
    }
    .date-string {
      color: var(--date-widget-date-color, #ddd);
      font-size: 1.5rem;
    }
    @media screen and (max-width: 1900px) {
      svg {
        width: 18px;
        height: 18px;
      }
      .container {
        max-width: 200px;
      }
      .date-string {
        font-size: 0.8rem;
      }
    }
  `;
}

window.customElements.define("date-widget", DateWidget);
