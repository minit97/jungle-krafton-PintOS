/* anon.c: Implementation of page for non-disk image (a.k.a. anonymous page). */

#include "vm/vm.h"
#include "devices/disk.h"
#include "lib/kernel/bitmap.h"

/* DO NOT MODIFY BELOW LINE */
static struct disk *swap_disk;
static bool anon_swap_in (struct page *page, void *kva);
static bool anon_swap_out (struct page *page);
static void anon_destroy (struct page *page);

/*
	Project 3: Swap In/Out

	swap_table: 스왑 디스크에서 사용 가능한 영역과 사용된 영역을 관리하기 위함
	비트가 0이면 해당 페이지를 사용 가능한 영역으로 선정
	1이면 참조 비트를 0으로 재설정하고 이때 변경 내용을 항상 디스크에 저장

	SECTORS_PER_PAGE: 스왑 영역은 PGSIZE 단위로 관리됨
	섹터(Sector)는 하드 드라이브의 최소 기억 단위
	이를 페이지 단위로 관리하려면 섹터 단위를 페이지 단위로 변경해야 함
	이게 SECTORS_PER_PAGE, 즉 8섹터 당 1페이지를 뜻함
*/
struct bitmap *swap_table;
static struct lock bitmap_lock;

/* DO NOT MODIFY this struct */
static const struct page_operations anon_ops = {
	.swap_in = anon_swap_in,
	.swap_out = anon_swap_out,
	.destroy = anon_destroy,
	.type = VM_ANON,
};

/* Initialize the data for anonymous pages */
void
vm_anon_init (void) {
    // Anonymous page의 subsystem을 초기화하는 함수

	/* Set up the swap_disk. */
	swap_disk = disk_get(1, 1);

    size_t swap_size = disk_size(swap_disk);
    // bitmap_create : 모든 비트들을 false로 초기화
    swap_table = bitmap_create(swap_size);
    lock_init(&bitmap_lock);
}

/* Initialize the file mapping */
bool
anon_initializer (struct page *page, enum vm_type type, void *kva) {
	/* Set up the handler */
	page->operations = &anon_ops;

	struct anon_page *anon_page = &page->anon;
    anon_page->index = -1;
    anon_page->thread = thread_current();
}

/* Swap in the page by read contents from the swap disk. */
static bool
anon_swap_in (struct page *page, void *kva) {
	struct anon_page *anon_page = &page->anon;
}

/* Swap out the page by writing contents to the swap disk. */
static bool
anon_swap_out (struct page *page) {
	struct anon_page *anon_page = &page->anon;
}

/* Destroy the anonymous page. PAGE will be freed by the caller. */
static void anon_destroy (struct page *page) {
    // Anon Page가 보유한 리소스를 해제

	struct anon_page *anon_page = &page->anon;
    disk_sector_t index = anon_page->index;

    if (page->frame != NULL) {
        lock_acquire(&frame_lock);
        list_remove(&page->frame->frame_elem);
        lock_release(&frame_lock);

        free(page->frame);
    }

    if (index != -1) {
        bitmap_set_multiple(swap_table, index, 8, false);
    }
}
