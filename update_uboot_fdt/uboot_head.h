
#ifndef  __spare_head_h__
#define  __spare_head_h__


#define UBOOT_MAGIC				"uboot"
#define MAGIC_SIZE              8

typedef struct _normal_gpio_cfg
{
    char      port;                       //�˿ں�
    char      port_num;                   //�˿��ڱ��
    char      mul_sel;                    //���ܱ��
    char      pull;                       //����״̬
    char      drv_level;                  //������������
    char      data;                       //�����ƽ
    char      reserved[2];                //����λ����֤����
}
normal_gpio_cfg;

/******************************************************************************/
/*               the control information stored in file head                  */
/******************************************************************************/
struct spare_boot_ctrl_head
{
	unsigned int  jump_instruction;   // one intruction jumping to real code
	unsigned char magic[MAGIC_SIZE];  // ="u-boot"
	unsigned int  check_sum;          // generated by PC
	unsigned int  align_size;		  // align size in byte
	unsigned int  length;             // the size of all file
	unsigned int  uboot_length;       // the size of uboot
	unsigned char version[8];         // uboot version
	unsigned char platform[8];        // platform information
	int           reserved[1];        //stamp space, 16bytes align
};

/******************************************************************************/
/*                          the data stored in file head                      */
/******************************************************************************/
struct spare_boot_data_head
{
	unsigned int                dram_para[32];
	int							run_clock;				// Mhz
	int							run_core_vol;			// mV
	int							uart_port;              // UART���������
	normal_gpio_cfg             uart_gpio[2];           // UART������(���Դ�ӡ��)GPIO��Ϣ
	int							twi_port;               // TWI���������
	normal_gpio_cfg             twi_gpio[2];            // TWI������GPIO��Ϣ�����ڿ���TWI
	int		                    work_mode;              // ����ģʽ
    int                         storage_type;           // �洢��������  0��nand   1��sdcard    2: spinor
    normal_gpio_cfg             nand_gpio[32];          // nand GPIO��Ϣ
    char						nand_spare_data[256];	// nand ������Ϣ
    normal_gpio_cfg             sdcard_gpio[32];		// sdcard GPIO��Ϣ
    char             			sdcard_spare_data[256];	// sdcard ������Ϣ
    int                         secureos_exist;
    int				            dtb_offset;			
    int							reserved[4];			// ��������λ, 256bytes align

};

struct spare_boot_head_t
{
	struct spare_boot_ctrl_head    boot_head;
	struct spare_boot_data_head    boot_data;
};
#endif