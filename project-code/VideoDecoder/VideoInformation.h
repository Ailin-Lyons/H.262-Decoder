//
// Created by elnsa on 2020-01-16.
//

#ifndef PROJECT_CODE_VIDEOINFORMATION_H
#define PROJECT_CODE_VIDEOINFORMATION_H

class VideoInformation {
public:
    enum class aspect_ratio {
        reserved_a_r,
        square_sample,
        ar_3_by_4,
        ar_9_by_16,
        ar_1_by_2_p_21
    };

    enum class video_profile {
        p_reserved,
        p_simple,
        p_main,
        p_snr_scalable,
        p_spatially_scalable,
        p_high,
        p_multi_view
    };

    void setProfileLevel(unsigned char profile_and_level_indication);

    enum class video_level {
        l_reserved,
        l_low,
        l_main,
        l_high_1440,
        l_high
    };

    enum class chroma_types {
        c_reserved,
        c_4_2_0,
        c_4_2_2,
        c_4_4_4
    };

private:
    static VideoInformation *instance;
    /**
     * Fields // H.262 6.3.3, 6.3.5
     */
    unsigned short horizontal_size; // 14-bits
    unsigned short vertical_size; // 14-bits
    aspect_ratio aspectRatio;
    double frameRate;
    unsigned int bit_rate; // 30-bits
    unsigned int vbv_buffer_size; //18-bits
    video_profile profile; // H.262 8
    video_level level; // H.262 8
    bool progressive_sequence;
    chroma_types chroma_format;
    bool low_delay;

    /**
     * A private constructor for the singleton
     */
    VideoInformation() = default;

    /**
     * Helper Functions
     */
    void setProfile(unsigned char profile_bits);

    void setLevel(unsigned char level_bits);

public:

    static VideoInformation *getInstance() {
        if (!instance) {
            instance = new VideoInformation();
        }
        return instance;
    }

    /**
     * Public Functions
     */

    unsigned short getHorizontalSize() const;

    unsigned short getVerticalSize() const;

    void setHorizontalSize(unsigned short horizontalSize);

    void setVerticalSize(unsigned short verticalSize);

    void setAspectRatio(unsigned char aspect_ratio_information);

    void setBitRate(unsigned int bitRate);

    void setVBVBufSize(unsigned int vbvBufferSize);

    void setProgressiveSequence(bool prog_sequence);

    void setChromaFormat(unsigned char chroma_bits);

    void setLowDelay(bool d);

    void setFrameRate(unsigned char frame_code, unsigned char frame_ext_n, unsigned char frame_ext_d);

    void print();
};

#endif //PROJECT_CODE_VIDEOINFORMATION_H
