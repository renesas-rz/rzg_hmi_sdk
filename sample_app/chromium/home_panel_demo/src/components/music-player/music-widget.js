import { LitElement, css, html, svg } from "lit";
import { classMap } from "lit/directives/class-map.js";

import { trackList } from "./track-list";

export class MusicWidget extends LitElement {
  // Define reactive properties
  static properties = {
    // internal states
    _trackIndex: { state: true },
    _trackName: { state: true },
    _trackArtist: { state: true },
    _currentTime: { state: true },
    _totalDuration: { state: true },
    _currentVolume: { state: true },
    _isPlaying: { state: true },
    _isLoop: { state: true },
    _isMuted: { state: true },
    _isLowVolume: { state: true },
    _isHighVolume: { state: true },
  };

  constructor() {
    super();
    // internal properties
    this.timer = undefined;

    // set the default internal states
    this._trackIndex = 0;
    this._trackName = "Track Name";
    this._trackArtist = "Track Artist";
    this._currentTime = "00:00";
    this._totalDuration = "00:00";
    this._currentVolume = 100;
    this._isPlaying = false;
    this._isLoop = false;
    this._isMuted = false;
    this._isLowVolume = false;
    this._isHighVolume = false;
    this.setUpdate = this.setUpdate.bind(this);
  }

  // Invoked when the custom element is added to the document's DOM.
  connectedCallback() {
    super.connectedCallback();

    // create an audio element
    this.track = document.createElement("audio");
    // set track name and artist
    this._trackName = trackList[this._trackIndex].name;
    this._trackArtist = trackList[this._trackIndex].artist;
  }

  // Invoked when the custom element is removed from the document's DOM.
  disconnectedCallback() {
    super.disconnectedCallback();
    // stop the audio
    this.track.pause();
    // remove the audio element
    this.track.remove();
  }

  // query the div.track-art element in the internal DOM using getter pattern
  get _trackArt() {
    return this.renderRoot.querySelector(".track-art");
  }

  // query the input.seek-slider element in the internal DOM using getter pattern
  get _seekSlider() {
    return this.renderRoot.querySelector(".seek-slider");
  }

  // query the input.volume-slider element in the internal DOM using getter pattern
  get _volumeSlider() {
    return this.renderRoot.querySelector(".volume-slider");
  }

  // Invoked when the custom element is initially rendered
  firstUpdated() {
    this.loadTrack(this._trackIndex);
  }

  /**
   * load the music tracks
   * @param {number} trackIndex the track index in the array
   */
  loadTrack(trackIndex) {
    clearInterval(this.timer);
    this.reset();

    this.track.src = trackList[trackIndex].path;
    this._trackArt.style.backgroundImage =
      "url(" + trackList[trackIndex].img + ")";
    this._trackName = trackList[trackIndex].name;
    this._trackArtist = trackList[trackIndex].artist;

    this.track.load();

    this.timer = setInterval(this.setUpdate, 1000);
  }

  /**
   * Reset the playback time
   */
  reset() {
    this._currentTime = "00:00";
    this._totalDuration = "00:00";
    this._seekSlider.value = 0;
  }

  /**
   * Repeat the current track
   */
  repeatTrack() {
    const currentIndex = this._trackIndex;
    this.loadTrack(currentIndex);
    this._isPlaying && this.playTrack();
  }

  /**
   * Enable looping through all track
   */
  loopTrack() {
    this._isLoop = !this._isLoop;
  }

  /**
   * Play or Pause the track
   */
  playPauseTrack() {
    this._isPlaying ? this.pauseTrack() : this.playTrack();
  }

  /**
   * Play the track
   */
  playTrack() {
    this.track.play();
    this._isPlaying = true;
  }

  /**
   * Pause the track
   */
  pauseTrack() {
    this.track.pause();
    this._isPlaying = false;
  }

  /**
   * Go to the next track
   */
  nextTrack() {
    if (this._trackIndex < trackList.length - 1) {
      this._trackIndex += 1;
    } else {
      this._trackIndex = 0;
    }

    this.loadTrack(this._trackIndex);
    this._isPlaying && this.playTrack();
  }

  /**
   * Go to the previous track
   */
  prevTrack() {
    if (this._trackIndex > 0) {
      this._trackIndex -= 1;
    } else {
      this._trackIndex = trackList.length - 1;
    }

    this.loadTrack(this._trackIndex);
    this._isPlaying && this.playTrack();
  }

  /**
   * Seek to a particular playback time
   */
  seekTo() {
    const seekto = this.track.duration * (this._seekSlider.value / 100);
    this.track.currentTime = seekto;
  }

  /**
   * Set the audio volume
   */
  setVolume() {
    this.track.volume = this._volumeSlider.value / 100;
    this._currentVolume = this.track.volume;

    if (this.track.volume > 0.5) {
      this._isMuted = false;
      this._isLowVolume = false;
      this._isHighVolume = true;
    } else if (this.track.volume <= 0.5 && this.track.volume > 0) {
      this._isMuted = false;
      this._isLowVolume = true;
      this._isHighVolume = false;
    } else {
      this._isMuted = true;
      this._isLowVolume = false;
      this._isHighVolume = false;
    }
  }

  /**
   * Mute the audio volume
   */
  muteVolume() {
    if (!this._isMuted) {
      this.track.volume = 0;
    } else {
      this.track.volume = this._volumeSlider.value / 100;
    }
    this._isMuted = !this._isMuted;
  }

  /**
   * Update the audio playback time
   */
  setUpdate() {
    let seekPosition = 0;
    if (!isNaN(this.track.duration)) {
      seekPosition = this.track.currentTime * (100 / this.track.duration);
      this._seekSlider.value = seekPosition;

      let currentMinutes = Math.floor(this.track.currentTime / 60);
      let currentSeconds = Math.floor(
        this.track.currentTime - currentMinutes * 60
      );
      let durationMinutes = Math.floor(this.track.duration / 60);
      let durationSeconds = Math.floor(
        this.track.duration - durationMinutes * 60
      );

      if (currentSeconds < 10) {
        currentSeconds = "0" + currentSeconds;
      }
      if (durationSeconds < 10) {
        durationSeconds = "0" + durationSeconds;
      }
      if (currentMinutes < 10) {
        currentMinutes = "0" + currentMinutes;
      }
      if (durationMinutes < 10) {
        durationMinutes = "0" + durationMinutes;
      }

      this._currentTime = currentMinutes + ":" + currentSeconds;
      this._totalDuration = durationMinutes + ":" + durationSeconds;

      if (this._currentTime >= this._totalDuration) {
        if (this._isLoop) {
          this._isPlaying = true;
          this.nextTrack();
        } else {
          this._isPlaying = false;
        }
      }
    }
  }

  render() {
    // apply classes dynamically
    const playedClasses = {
      // apply "loader" class when the given property is set to true
      loader: this._isPlaying,
    };
    const loopActiveClasses = {
      // apply "loop-active" class when the given property is set to true
      "loop-active": this._isLoop,
    };
    return html`
      <div class="player">
        <div class="details">
          <div class="now-playing">
            Playing ${this._trackIndex + 1} of ${trackList.length}
          </div>
          <div class="track-art"></div>
          <div class="track-name">${this._trackName}</div>
          <div class="track-artist">${this._trackArtist}</div>
        </div>
        <div class="slider-container">
          <div class="current-time">${this._currentTime}</div>
          <input
            type="range"
            min="1"
            max="100"
            value="0"
            class="seek-slider"
            @change=${this.seekTo}
          />
          <div class="total-duration">${this._totalDuration}</div>
        </div>
        <div class="slider-container">
          <div class="volume-mute" @click=${this.muteVolume}>
            ${this._isMuted
              ? svg`
                <svg xmlns="http://www.w3.org/2000/svg" height="24px" viewBox="0 -960 960 960" width="24px" fill="#5f6368" class="volume-icon">
                  <path d="m616-320-56-56 104-104-104-104 56-56 104 104 104-104 56 56-104 104 104 104-56 56-104-104-104 104Zm-496-40v-240h160l200-200v640L280-360H120Z"/>
                </svg>
              `
              : this._isLowVolume
              ? svg`
                <svg xmlns="http://www.w3.org/2000/svg" height="24px" viewBox="0 -960 960 960" width="24px" fill="#5f6368" class="volume-icon">
                  <path d="M200-360v-240h160l200-200v640L360-360H200Zm440 40v-322q45 21 72.5 65t27.5 97q0 53-27.5 96T640-320Z"/>
                </svg>
              `
              : svg`
                <svg xmlns="http://www.w3.org/2000/svg" height="24px" viewBox="0 -960 960 960" width="24px" fill="#5f6368" class="volume-icon">
                  <path d="M560-131v-82q90-26 145-100t55-168q0-94-55-168T560-749v-82q124 28 202 125.5T840-481q0 127-78 224.5T560-131ZM120-360v-240h160l200-200v640L280-360H120Zm440 40v-322q47 22 73.5 66t26.5 96q0 51-26.5 94.5T560-320Z"/>
                </svg>
              `}
          </div>
          <input
            type="range"
            min="0"
            max="100"
            value=${this._currentVolume}
            class="volume-slider"
            @change=${this.setVolume}
          />
          <div class="volume-value">${Math.ceil(this.track.volume * 100)}</div>
        </div>
        <div class="buttons">
          <div
            class="loop-track ${classMap(loopActiveClasses)}"
            @click=${this.loopTrack}
          >
            <svg
              xmlns="http://www.w3.org/2000/svg"
              height="24px"
              viewBox="0 -960 960 960"
              width="24px"
              fill="#5f6368"
            >
              <path
                d="M280-80 120-240l160-160 56 58-62 62h406v-160h80v240H274l62 62-56 58Zm-80-440v-240h486l-62-62 56-58 160 160-160 160-56-58 62-62H280v160h-80Z"
              />
            </svg>
          </div>
          <div class="prev-track" @click=${this.prevTrack}>
            <svg
              xmlns="http://www.w3.org/2000/svg"
              height="24px"
              viewBox="0 -960 960 960"
              width="24px"
              fill="#5f6368"
            >
              <path d="M220-240v-480h80v480h-80Zm520 0L380-480l360-240v480Z" />
            </svg>
          </div>
          <div class="playpause-track" @click=${this.playPauseTrack}>
            ${this._isPlaying
              ? svg`
                <svg xmlns="http://www.w3.org/2000/svg" height="48px" viewBox="0 -960 960 960" width="48px" fill="#5f6368">
                  <path d="M360-320h80v-320h-80v320Zm160 0h80v-320h-80v320ZM480-80q-83 0-156-31.5T197-197q-54-54-85.5-127T80-480q0-83 31.5-156T197-763q54-54 127-85.5T480-880q83 0 156 31.5T763-763q54 54 85.5 127T880-480q0 83-31.5 156T763-197q-54 54-127 85.5T480-80Z"/>
                </svg>
              `
              : svg`
                <svg xmlns="http://www.w3.org/2000/svg" height="48px" viewBox="0 -960 960 960" width="48px" fill="#5f6368">
                  <path d="m380-300 280-180-280-180v360ZM480-80q-83 0-156-31.5T197-197q-54-54-85.5-127T80-480q0-83 31.5-156T197-763q54-54 127-85.5T480-880q83 0 156 31.5T763-763q54 54 85.5 127T880-480q0 83-31.5 156T763-197q-54 54-127 85.5T480-80Z"/>
                </svg>
              `}
          </div>
          <div class="next-track" @click=${this.nextTrack}>
            <svg
              xmlns="http://www.w3.org/2000/svg"
              height="24px"
              viewBox="0 -960 960 960"
              width="24px"
              fill="#5f6368"
            >
              <path
                d="M660-240v-480h80v480h-80Zm-440 0v-480l360 240-360 240Z"
              />
            </svg>
          </div>
          <div class="repeat-track" @click=${this.repeatTrack}>
            <svg
              xmlns="http://www.w3.org/2000/svg"
              height="24px"
              viewBox="0 -960 960 960"
              width="24px"
              fill="#5f6368"
            >
              <path
                d="M480-80q-75 0-140.5-28.5t-114-77q-48.5-48.5-77-114T120-440h80q0 117 81.5 198.5T480-160q117 0 198.5-81.5T760-440q0-117-81.5-198.5T480-720h-6l62 62-56 58-160-160 160-160 56 58-62 62h6q75 0 140.5 28.5t114 77q48.5 48.5 77 114T840-440q0 75-28.5 140.5t-77 114q-48.5 48.5-114 77T480-80Z"
              />
            </svg>
          </div>
        </div>
        <div class="wave ${classMap(playedClasses)}">
          <span class="stroke"></span>
          <span class="stroke"></span>
          <span class="stroke"></span>
          <span class="stroke"></span>
          <span class="stroke"></span>
          <span class="stroke"></span>
          <span class="stroke"></span>
        </div>
      </div>
    `;
  }

  static styles = css`
    :host {
      display: block;
      height: 100%;
    }
    .player {
      box-sizing: border-box;
      width: 100%;
      height: 100%;
      border: 1px solid transparent;
      display: flex;
      flex-direction: column;
      justify-content: center;
      align-items: center;
      padding: 1rem;
      border-radius: 20px;
      background-color: #ced4da;
    }
    .details {
      display: flex;
      flex-direction: column;
      justify-content: center;
      align-items: center;
    }
    .track-art {
      margin: 24px;
      height: 160px;
      width: 160px;
      border: 2px solid #fff;
      background-size: cover;
      background-position: center;
      border-radius: 50%;
      box-shadow: 0pc 6px 5px #ccc;
    }
    .now-playing {
      font-size: 1.5rem;
    }
    .track-name {
      font-size: 2.3rem;
      font-weight: bold;
    }
    .track-artist {
      font-size: 2rem;
      margin: 16px 0;
    }
    .buttons {
      display: flex;
      flex-direction: row;
      align-items: center;
    }
    .buttons svg {
      transition: fill 500ms;
      cursor: pointer;
    }
    .buttons svg:hover {
      fill: #2a2929;
    }
    .loop-active svg {
      fill: #3774ff;
    }
    .loop-active svg:hover {
      fill: #2f419a;
    }
    .repeat-track,
    .loop-track,
    .playpause-track,
    .prev-track,
    .next-track {
      padding: 0.8rem;
    }
    .repeat-track svg,
    .loop-track svg,
    .prev-track svg,
    .next-track svg {
      width: 36px;
      height: 36px;
    }
    .playpause-track svg {
      width: 64px;
      height: 64px;
    }
    .slider-container {
      width: 100%;
      display: flex;
      justify-content: center;
      align-items: center;
    }
    .seek-slider,
    .volume-slider {
      appearance: none;
      height: 8px;
      background-color: #83a9ff;
    }
    .seek-slider::-webkit-slider-thumb,
    .volume-slider::-webkit-slider-thumb {
      -webkit-appearance: none;
      appearance: none;
      width: 30px;
      height: 30px;
      background-color: #fff;
      border: 3px solid #3774ff;
      cursor: pointer;
      border-radius: 100%;
    }
    .seek-slider {
      width: 60%;
    }
    .volume-slider {
      width: 80%;
    }
    .current-time,
    .total-duration,
    .volume-value {
      font-size: 1.5rem;
    }
    .current-time,
    .total-duration {
      padding: 10px;
    }
    .volume-mute {
      cursor: pointer;
    }
    .volume-mute svg {
      width: 32px;
      height: 32px;
    }
    .volume-icon {
      padding: 10px;
    }
    .volume-value {
      width: 36px;
      padding: 10px;
    }
    .wave {
      height: 70px;
      width: 100%;
      display: flex;
      justify-content: center;
      align-items: center;
    }
    .wave .stroke {
      background-color: #4286f4;
      height: 5%;
      width: 10px;
      border-radius: 50px;
      margin: 0px 5px;
    }
    .loader .stroke {
      background-color: #f1f1f1;
      height: 100%;
      width: 10px;
      border-radius: 50px;
      margin: 0px 5px;
      animation: animate 1.4s infinite linear;
    }
    @keyframes animate {
      50% {
        height: 20%;
        background-color: #4286f4;
      }
      100% {
        height: 100%;
      }
    }
    .stroke:nth-child(1) {
      animation-delay: 0s;
    }
    .stroke:nth-child(2) {
      animation-delay: 0.3s;
    }
    .stroke:nth-child(3) {
      animation-delay: 0.6s;
    }
    .stroke:nth-child(4) {
      animation-delay: 0.9s;
    }
    .stroke:nth-child(5) {
      animation-delay: 0.6s;
    }
    .stroke:nth-child(6) {
      animation-delay: 0.3s;
    }
    .stroke:nth-child(7) {
      animation-delay: 0s;
    }

    @media screen and (max-height: 800px) {
      .track-art {
        margin: 16px;
        height: 140px;
        width: 140px;
      }
      .now-playing {
        font-size: 1rem;
      }
      .track-name {
        font-size: 1.8rem;
      }
      .track-artist {
        font-size: 1.2rem;
        margin-top: 5px;
      }
      .seek-slider,
      .volume-slider {
        height: 5px;
      }
      .seek-slider::-webkit-slider-thumb,
      .volume-slider::-webkit-slider-thumb {
        width: 15px;
        height: 15px;
      }
      .current-time,
      .total-duration,
      .volume-value {
        font-size: 1rem;
      }
      .repeat-track svg,
      .loop-track svg,
      .prev-track svg,
      .next-track svg {
        width: 24px;
        height: 24px;
      }
      .playpause-track svg {
        width: 48px;
        height: 48px;
      }
      .volume-mute svg {
        width: 24px;
        height: 24px;
      }
    }
  `;
}

window.customElements.define("music-widget", MusicWidget);
